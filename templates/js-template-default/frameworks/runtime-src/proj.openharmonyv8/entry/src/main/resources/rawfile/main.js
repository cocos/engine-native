function hotUpdate () {
  if (typeof globalThis.jsb === 'object') {
    var hotUpdateSearchPaths = globalThis.cc.sys.localStorage.getItem('HotUpdateSearchPaths');
    if (hotUpdateSearchPaths) {
      var paths = JSON.parse(hotUpdateSearchPaths);
      globalThis.jsb.fileUtils.setSearchPaths(paths);

      var fileList = [];
      var storagePath = paths[0] || '';
      var tempPath = storagePath + '_temp/';
      var baseOffset = tempPath.length;

      if (globalThis.jsb.fileUtils.isDirectoryExist(tempPath) && !globalThis.jsb.fileUtils.isFileExist(tempPath + 'project.manifest.temp')) {
        globalThis.jsb.fileUtils.listFilesRecursively(tempPath, fileList);
        fileList.forEach(srcPath => {
          var relativePath = srcPath.substr(baseOffset);
          var dstPath = storagePath + relativePath;
          if (srcPath[srcPath.length] == '/') {
            globalThis.jsb.fileUtils.createDirectory(dstPath)
          }
          else {
            if (globalThis.jsb.fileUtils.isFileExist(dstPath)) {
              globalThis.jsb.fileUtils.removeFile(dstPath)
            }
            globalThis.jsb.fileUtils.renameFile(srcPath, dstPath);
          }
        })
        globalThis.jsb.fileUtils.removeDirectory(tempPath);
      }
    }
  }
};

function loadJsList (jsList, cb)  {
  globalThis.cc.assetManager.loadScript(jsList.map(function (x) { return x; }), cb);
};


function boot() {
  const cc = globalThis.cc;
  var settings = globalThis._CCSettings;
  globalThis._CCSettings = undefined;
  var onProgress = null;

  var RESOURCES = cc.AssetManager.BuiltinBundleName.RESOURCES;
  var INTERNAL = cc.AssetManager.BuiltinBundleName.INTERNAL;
  var MAIN = cc.AssetManager.BuiltinBundleName.MAIN;
  cc.macro.CLEANUP_IMAGE_CACHE = true
  var onStart = function () {
    cc.view.enableRetina(true);
    cc.view.resizeWithBrowserSize(true);

    if (settings.orientation === 'landscape') {
      cc.view.setOrientation(cc.macro.ORIENTATION_LANDSCAPE);
    }
    else if (settings.orientation === 'portrait') {
      cc.view.setOrientation(cc.macro.ORIENTATION_PORTRAIT);
    }
    cc.view.enableAutoFullScreen([
      cc.sys.BROWSER_TYPE_BAIDU,
      cc.sys.BROWSER_TYPE_BAIDU_APP,
      cc.sys.BROWSER_TYPE_WECHAT,
      cc.sys.BROWSER_TYPE_MOBILE_QQ,
      cc.sys.BROWSER_TYPE_MIUI,
      cc.sys.BROWSER_TYPE_HUAWEI,
      cc.sys.BROWSER_TYPE_UC,
    ].indexOf(cc.sys.browserType) < 0);

    var launchScene = settings.launchScene;
    var bundle = cc.assetManager.bundles.find(function (b) {
      return b.getSceneInfo(launchScene);
    });

    bundle.loadScene(launchScene, null, onProgress,
      function (err, scene) {
        if (!err) {
          cc.director.runSceneImmediate(scene);
        }
      }
    );
  };

  var option = {
    id: 'GameCanvas',
    debugMode: settings.debug ? cc.debug.DebugMode.INFO : cc.debug.DebugMode.ERROR,
    showFPS: settings.debug,
    frameRate: 60,
    groupList: settings.groupList,
    collisionMatrix: settings.collisionMatrix,
  };

  cc.assetManager.init({
    bundleVers: settings.bundleVers,
    remoteBundles: settings.remoteBundles,
    server: settings.server
  });

  var bundleRoot = [INTERNAL];
  settings.hasResourcesBundle && bundleRoot.push(RESOURCES);

  var count = 0;
  function cb(err) {
    if (err) {
      return console.error(err.message, err.stack);
    }
    count++;
    if (count === bundleRoot.length + 1) {
      cc.assetManager.loadBundle(MAIN, function (err) {
        if (!err) cc.game.run(option, onStart);
      });
    }
  }
  loadJsList(settings.jsList,cb);

  for (var i = 0; i < bundleRoot.length; i++) {
    cc.assetManager.loadBundle(bundleRoot[i], cb);
  }

};

async function launchEngine() {
  globalThis.require('src/settings.js');
  globalThis.require('jsb-adapter/jsb-builtin.js');
  globalThis.require('src/cocos2d-jsb.js');
  globalThis.require('src/physics.js');
  globalThis.require('jsb-adapter/jsb-engine.js');
  hotUpdate();
  boot();
}
launchEngine();
