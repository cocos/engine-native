(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
require('./jsb-reflection.js');

require('./jsb-assets-manager.js');

require('./jsb-sys.js');

require('./jsb-game.js');

require('./jsb-gfx.js');

require('./jsb-loader.js');

require('./jsb-videoplayer.js');

require('./jsb-webview.js');

require('./jsb-audio.js');

require('./jsb-editbox.js');

require('./jsb-pipeline.js');

require('./jsb-safearea.js');

require('./jsb-editor-support.js');

require('./jsb-spine-skeleton.js');

require('./jsb-dragonbones.js');

},{"./jsb-assets-manager.js":2,"./jsb-audio.js":3,"./jsb-dragonbones.js":5,"./jsb-editbox.js":6,"./jsb-editor-support.js":7,"./jsb-game.js":9,"./jsb-gfx.js":10,"./jsb-loader.js":11,"./jsb-pipeline.js":12,"./jsb-reflection.js":13,"./jsb-safearea.js":14,"./jsb-spine-skeleton.js":15,"./jsb-sys.js":16,"./jsb-videoplayer.js":17,"./jsb-webview.js":18}],2:[function(require,module,exports){
"use strict";

/*
 * Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
if (jsb.AssetsManager) {
  jsb.AssetsManager.State = {
    UNINITED: 0,
    UNCHECKED: 1,
    PREDOWNLOAD_VERSION: 2,
    DOWNLOADING_VERSION: 3,
    VERSION_LOADED: 4,
    PREDOWNLOAD_MANIFEST: 5,
    DOWNLOADING_MANIFEST: 6,
    MANIFEST_LOADED: 7,
    NEED_UPDATE: 8,
    READY_TO_UPDATE: 9,
    UPDATING: 10,
    UNZIPPING: 11,
    UP_TO_DATE: 12,
    FAIL_TO_UPDATE: 13
  };
  jsb.Manifest.DownloadState = {
    UNSTARTED: 0,
    DOWNLOADING: 1,
    SUCCESSED: 2,
    UNMARKED: 3
  };
  jsb.EventAssetsManager.ERROR_NO_LOCAL_MANIFEST = 0;
  jsb.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST = 1;
  jsb.EventAssetsManager.ERROR_PARSE_MANIFEST = 2;
  jsb.EventAssetsManager.NEW_VERSION_FOUND = 3;
  jsb.EventAssetsManager.ALREADY_UP_TO_DATE = 4;
  jsb.EventAssetsManager.UPDATE_PROGRESSION = 5;
  jsb.EventAssetsManager.ASSET_UPDATED = 6;
  jsb.EventAssetsManager.ERROR_UPDATING = 7;
  jsb.EventAssetsManager.UPDATE_FINISHED = 8;
  jsb.EventAssetsManager.UPDATE_FAILED = 9;
  jsb.EventAssetsManager.ERROR_DECOMPRESS = 10;
}

},{}],3:[function(require,module,exports){
/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2020 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and  non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
'use strict';

const AudioPlayer = cc.internal.AudioPlayer;

if (AudioPlayer) {
  const {
    PlayingState,
    AudioType
  } = cc.AudioClip;

  cc.AudioClip.prototype._getPlayer = function (clip) {
    this._loadMode = AudioType.JSB_AUDIO;
    return AudioPlayerJSB;
  };

  class AudioPlayerJSB extends AudioPlayer {
    constructor(info) {
      super(info);
      this._startTime = 0;
      this._offset = 0;
      this._volume = 1;
      this._loop = false;
      this._url = info.nativeAudio;
      this._audio = -1;
      this._onEnded = this._onEnded.bind(this);
    }

    play() {
      if (this._state === PlayingState.PLAYING) {
        return;
      }

      if (this._blocking) {
        this._interrupted = true;
        return;
      }

      this._doPlay(); // delay eval here to yield uniform behavior with other platforms


      cc.director.once(cc.Director.EVENT_AFTER_UPDATE, this._onPlay, this);
    }

    pause() {
      if (this._audio < 0) {
        return;
      }

      this._interrupted = false;

      if (this._state !== PlayingState.PLAYING) {
        return;
      }

      jsb.AudioEngine.pause(this._audio);

      this._onPause();
    }

    stop() {
      if (this._audio < 0) {
        return;
      }

      this._interrupted = false;
      jsb.AudioEngine.stop(this._audio);
      this._audio = -1;

      this._onStop();
    }

    playOneShot(volume) {
      if (volume === undefined) {
        volume = 1;
      }

      jsb.AudioEngine.play(this._url, false, volume);
    }

    getCurrentTime() {
      if (this._state !== PlayingState.PLAYING) {
        return this._offset / 1000;
      }

      let current = (performance.now() - this._startTime + this._offset) / 1000;

      while (current > this._duration) {
        if (this._loop) {
          current -= this._duration;
          this._startTime += this._duration * 1000;
        } else current = 0; // onEnded callback may lag behind a few frames

      }

      return current;
    }

    setCurrentTime(val) {
      if (this._audio < 0) {
        return;
      }

      val = cc.math.clamp(val, 0, this._duration);
      jsb.AudioEngine.setCurrentTime(this._audio, val);
      this._offset = val * 1000;
      this._startTime = performance.now();
    }

    getVolume() {
      return this._volume;
    }

    setVolume(val, immediate) {
      this._volume = val;

      if (this._audio >= 0) {
        jsb.AudioEngine.setVolume(this._audio, val);
      }
    }

    getLoop() {
      return this._loop;
    }

    setLoop(val) {
      this._loop = val;

      if (this._audio >= 0) {
        jsb.AudioEngine.setLoop(this._audio, val);
      }
    }

    destroy() {
      if (this._audio >= 0) {
        jsb.AudioEngine.uncache(this._url);
        this._audio = -1;
      }

      super.destroy();
    }

    _doPlay() {
      if (this._audio >= 0) jsb.AudioEngine.resume(this._audio);else {
        this._audio = jsb.AudioEngine.play(this._url, this._loop, this._volume);
        jsb.AudioEngine.setErrorCallback(this._audio, console.error);
        jsb.AudioEngine.setFinishCallback(this._audio, this._onEnded);
      }
    }

    _onPlay() {
      if (this._state === PlayingState.PLAYING) {
        return;
      }

      this._state = PlayingState.PLAYING;
      this._startTime = performance.now();

      this._clip.emit('started');
    }

    _onPause() {
      if (this._state === PlayingState.STOPPED) {
        return;
      }

      this._state = PlayingState.STOPPED;
      this._offset += performance.now() - this._startTime;
    }

    _onStop() {
      this._offset = 0;

      if (this._state === PlayingState.STOPPED) {
        return;
      }

      this._state = PlayingState.STOPPED;
    }

    _onEnded() {
      this._offset = 0;
      this._audio = -1;

      if (this._state === PlayingState.STOPPED) {
        return;
      }

      this._state = PlayingState.STOPPED;

      this._clip.emit('ended');
    }

  }
}

},{}],4:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.
 https://www.cocos.com/
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of cache-manager software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.
 The software or tools in cache-manager License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
const {
  getUserDataPath,
  readJsonSync,
  makeDirSync,
  writeFileSync,
  deleteFile,
  rmdirSync
} = require('./jsb-fs-utils');

var writeCacheFileList = null;
var cleaning = false;
const REGEX = /^\w+:\/\/.*/;
var cacheManager = {
  cacheDir: 'gamecaches',
  cachedFileName: 'cacheList.json',
  deleteInterval: 500,
  writeFileInterval: 2000,
  cachedFiles: null,
  version: '1.1',

  getCache(url) {
    this.updateLastTime(url);
    return this.cachedFiles.has(url) ? `${this.cacheDir}/${this.cachedFiles.get(url).url}` : '';
  },

  getTemp(url) {
    return '';
  },

  init() {
    this.cacheDir = getUserDataPath() + '/' + this.cacheDir;
    var cacheFilePath = this.cacheDir + '/' + this.cachedFileName;
    var result = readJsonSync(cacheFilePath);

    if (result instanceof Error || !result.version || result.version !== this.version) {
      if (!(result instanceof Error)) rmdirSync(this.cacheDir, true);
      this.cachedFiles = new cc.AssetManager.Cache();
      makeDirSync(this.cacheDir, true);
      writeFileSync(cacheFilePath, JSON.stringify({
        files: this.cachedFiles._map,
        version: this.version
      }), 'utf8');
    } else {
      this.cachedFiles = new cc.AssetManager.Cache(result.files);
    }
  },

  updateLastTime(url) {
    if (this.cachedFiles.has(url)) {
      var cache = this.cachedFiles.get(url);
      cache.lastTime = Date.now();
    }
  },

  _write() {
    writeCacheFileList = null;
    writeFileSync(this.cacheDir + '/' + this.cachedFileName, JSON.stringify({
      files: this.cachedFiles._map,
      version: this.version
    }), 'utf8');
  },

  writeCacheFile() {
    if (!writeCacheFileList) {
      writeCacheFileList = setTimeout(this._write.bind(this), this.writeFileInterval);
    }
  },

  cacheFile(id, url, cacheBundleRoot) {
    this.cachedFiles.add(id, {
      bundle: cacheBundleRoot,
      url,
      lastTime: Date.now()
    });
    this.writeCacheFile();
  },

  clearCache() {
    rmdirSync(this.cacheDir, true);
    this.cachedFiles = new cc.AssetManager.Cache();
    makeDirSync(this.cacheDir, true);
    clearTimeout(writeCacheFileList);

    this._write();

    cc.assetManager.bundles.forEach(bundle => {
      if (REGEX.test(bundle.base)) this.makeBundleFolder(bundle.name);
    });
  },

  clearLRU() {
    if (cleaning) return;
    cleaning = true;
    var caches = [];
    var self = this;
    this.cachedFiles.forEach((val, key) => {
      if (val.bundle === 'internal') return;
      caches.push({
        originUrl: key,
        url: this.getCache(key),
        lastTime: val.lastTime
      });
    });
    caches.sort(function (a, b) {
      return a.lastTime - b.lastTime;
    });
    caches.length = Math.floor(this.cachedFiles.count / 3);
    if (caches.length === 0) return;

    for (var i = 0, l = caches.length; i < l; i++) {
      this.cachedFiles.remove(caches[i].originUrl);
    }

    clearTimeout(writeCacheFileList);

    this._write();

    function deferredDelete() {
      var item = caches.pop();
      deleteFile(item.url);

      if (caches.length > 0) {
        setTimeout(deferredDelete, self.deleteInterval);
      } else {
        cleaning = false;
      }
    }

    setTimeout(deferredDelete, self.deleteInterval);
  },

  removeCache(url) {
    if (this.cachedFiles.has(url)) {
      var path = this.getCache(url);
      this.cachedFiles.remove(url);
      clearTimeout(writeCacheFileList);

      this._write();

      deleteFile(path);
    }
  },

  makeBundleFolder(bundleName) {
    makeDirSync(this.cacheDir + '/' + bundleName, true);
  }

};
cc.assetManager.cacheManager = module.exports = cacheManager;

},{"./jsb-fs-utils":8}],5:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
const cacheManager = require('./jsb-cache-manager');

(function () {
  if (window.dragonBones === undefined || window.middleware === undefined) return;
  let ArmatureDisplayComponent = cc.internal.ArmatureDisplay;
  if (ArmatureDisplayComponent === undefined) return; // dragonbones global time scale.

  Object.defineProperty(dragonBones, 'timeScale', {
    get() {
      return this._timeScale;
    },

    set(value) {
      this._timeScale = value;
      let factory = this.CCFactory.getInstance();
      factory.setTimeScale(value);
    },

    configurable: true
  });
  middleware.generateGetSet(dragonBones);

  let _slotColor = cc.color(0, 0, 255, 255);

  let _boneColor = cc.color(255, 0, 0, 255);

  let _originColor = cc.color(0, 255, 0, 255); ////////////////////////////////////////////////////////////
  // override dragonBones library by native dragonBones
  ////////////////////////////////////////////////////////////
  //--------------------
  // adapt event name
  //--------------------


  dragonBones.EventObject.START = "start";
  dragonBones.EventObject.LOOP_COMPLETE = "loopComplete";
  dragonBones.EventObject.COMPLETE = "complete";
  dragonBones.EventObject.FADE_IN = "fadeIn";
  dragonBones.EventObject.FADE_IN_COMPLETE = "fadeInComplete";
  dragonBones.EventObject.FADE_OUT = "fadeOut";
  dragonBones.EventObject.FADE_OUT_COMPLETE = "fadeOutComplete";
  dragonBones.EventObject.FRAME_EVENT = "frameEvent";
  dragonBones.EventObject.SOUND_EVENT = "soundEvent";
  dragonBones.DragonBones = {
    ANGLE_TO_RADIAN: Math.PI / 180,
    RADIAN_TO_ANGLE: 180 / Math.PI
  }; //-------------------
  // native factory
  //-------------------

  let factoryProto = dragonBones.CCFactory.prototype;

  factoryProto.createArmatureNode = function (comp, armatureName, node) {
    node = node || new cc.Node();
    let display = node.getComponent(ArmatureDisplayComponent);

    if (!display) {
      display = node.addComponent(ArmatureDisplayComponent);
    }

    node.name = armatureName;
    display._armatureName = armatureName;
    display._dragonAsset = comp.dragonAsset;
    display._dragonAtlasAsset = comp.dragonAtlasAsset;

    display._init();

    return display;
  };

  let _replaceSkin = factoryProto.replaceSkin;

  factoryProto.replaceSkin = function (armatrue, skinData, isOverride, exclude) {
    if (isOverride == undefined) isOverride = false;
    exclude = exclude || [];

    _replaceSkin.call(this, armatrue, skinData, isOverride, exclude);
  };

  let _changeSkin = factoryProto.changeSkin;

  factoryProto.changeSkin = function (armatrue, skinData, exclude) {
    _changeSkin.call(this, armatrue, skinData, exclude);
  };

  dragonBones.CCFactory.getInstance = function () {
    return dragonBones.CCFactory.getFactory();
  }; //-------------------
  // native animation state
  //-------------------


  let animationStateProto = dragonBones.AnimationState.prototype;
  let _isPlaying = animationStateProto.isPlaying;
  Object.defineProperty(animationStateProto, 'isPlaying', {
    get() {
      return _isPlaying.call(this);
    }

  }); //-------------------
  // native armature
  //-------------------

  let armatureProto = dragonBones.Armature.prototype;

  armatureProto.addEventListener = function (eventType, listener, target) {
    this.__persistentDisplay__ = this.getDisplay();

    this.__persistentDisplay__.on(eventType, listener, target);
  };

  armatureProto.removeEventListener = function (eventType, listener, target) {
    this.__persistentDisplay__ = this.getDisplay();

    this.__persistentDisplay__.off(eventType, listener, target);
  }; //--------------------------
  // native CCArmatureDisplay
  //--------------------------


  let nativeArmatureDisplayProto = dragonBones.CCArmatureDisplay.prototype;
  Object.defineProperty(nativeArmatureDisplayProto, "node", {
    get: function () {
      return this;
    }
  });

  nativeArmatureDisplayProto.getRootNode = function () {
    let rootDisplay = this.getRootDisplay();
    return rootDisplay && rootDisplay._ccNode;
  };

  nativeArmatureDisplayProto.convertToWorldSpace = function (point) {
    let newPos = this.convertToRootSpace(point.x, point.y);
    newPos = cc.v3(newPos.x, newPos.y, 0);
    let ccNode = this.getRootNode();
    if (!ccNode) return newPos;

    let finalPos = ccNode._uiProps.uiTransformComp.convertToWorldSpaceAR(newPos);

    return finalPos;
  };

  nativeArmatureDisplayProto.initEvent = function () {
    if (this._eventTarget) {
      return;
    }

    this._eventTarget = new cc.EventTarget();
    this.setDBEventCallback(function (eventObject) {
      this._eventTarget.emit(eventObject.type, eventObject);
    });
  };

  nativeArmatureDisplayProto.on = function (type, listener, target) {
    this.initEvent();

    this._eventTarget.on(type, listener, target);

    this.addDBEventListener(type, listener);
  };

  nativeArmatureDisplayProto.off = function (type, listener, target) {
    this.initEvent();

    this._eventTarget.off(type, listener, target);

    this.removeDBEventListener(type, listener);
  };

  nativeArmatureDisplayProto.once = function (type, listener, target) {
    this.initEvent();

    this._eventTarget.once(type, listener, target);

    this.addDBEventListener(type, listener);
  }; ////////////////////////////////////////////////////////////
  // override DragonBonesAtlasAsset
  ////////////////////////////////////////////////////////////


  let dbAtlas = cc.internal.DragonBonesAtlasAsset.prototype;
  let _gTextureIdx = 1;
  let _textureKeyMap = {};

  let _textureMap = new WeakMap();

  let _textureIdx2Name = {};

  dbAtlas.removeRecordTexture = function (texture) {
    if (!texture) return;
    delete _textureIdx2Name[texture.url];
    let index = texture.__textureIndex__;

    if (index) {
      let texKey = _textureKeyMap[index];

      if (texKey && _textureMap.has(texKey)) {
        _textureMap.delete(texKey);

        delete _textureKeyMap[index];
      }
    }
  };

  dbAtlas.recordTexture = function () {
    if (this._texture && this._oldTexture !== this._texture) {
      this.removeRecordTexture(this._oldTexture);
      let texKey = _textureKeyMap[_gTextureIdx] = {
        key: _gTextureIdx
      };

      _textureMap.set(texKey, this._texture);

      this._oldTexture = this._texture;
      this._texture.__textureIndex__ = _gTextureIdx;
      _gTextureIdx++;
    }
  };

  dbAtlas.getTextureByIndex = function (textureIdx) {
    let texKey = _textureKeyMap[textureIdx];
    if (!texKey) return;
    return _textureMap.get(texKey);
  };

  dbAtlas.updateTextureAtlasData = function (factory) {
    let url = this._texture.url;
    let preAtlasInfo = _textureIdx2Name[url];
    let index; // If the texture has store the atlas info before,then get native atlas object,and 
    // update script texture map.

    if (preAtlasInfo) {
      index = preAtlasInfo.index;
      this._textureAtlasData = factory.getTextureAtlasDataByIndex(preAtlasInfo.name, index);
      let texKey = _textureKeyMap[preAtlasInfo.index];

      _textureMap.set(texKey, this._texture);

      this._texture.__textureIndex__ = index; // If script has store the atlas info,but native has no atlas object,then
      // still new native texture2d object,but no call recordTexture to increase
      // textureIndex.

      if (this._textureAtlasData) {
        return;
      }
    } else {
      this.recordTexture();
    }

    index = this._texture.__textureIndex__;
    this.jsbTexture = new middleware.Texture2D();
    this.jsbTexture.setRealTextureIndex(index);
    this.jsbTexture.setPixelsWide(this._texture.width);
    this.jsbTexture.setPixelsHigh(this._texture.height);
    this._textureAtlasData = factory.parseTextureAtlasData(this.atlasJson, this.jsbTexture, this._uuid);
    _textureIdx2Name[url] = {
      name: this._textureAtlasData.name,
      index: index
    };
  };

  dbAtlas.init = function (factory) {
    this._factory = factory; // If create by manual, uuid is empty.

    if (!this._uuid) {
      let atlasJsonObj = JSON.parse(this.atlasJson);
      this._uuid = atlasJsonObj.name;
    }

    if (this._textureAtlasData) {
      factory.addTextureAtlasData(this._textureAtlasData, this._uuid);
    } else {
      this.updateTextureAtlasData(factory);
    }
  };

  dbAtlas._clear = function (dontRecordTexture) {
    if (this._factory) {
      this._factory.removeTextureAtlasData(this._uuid, true);

      this._factory.removeDragonBonesDataByUUID(this._uuid, true);
    }

    this._textureAtlasData = null;

    if (!dontRecordTexture) {
      this.recordTexture();
    }
  };

  dbAtlas.destroy = function () {
    this.removeRecordTexture(this._texture);

    this._clear(true);

    cc.Asset.prototype.destroy.call(this);
  }; ////////////////////////////////////////////////////////////
  // override DragonBonesAsset
  ////////////////////////////////////////////////////////////


  let dbAsset = cc.internal.DragonBonesAsset.prototype;

  dbAsset.init = function (factory, atlasUUID) {
    this._factory = factory; // If create by manual, uuid is empty.
    // Only support json format, if remote load dbbin, must set uuid by manual.

    if (!this._uuid && this.dragonBonesJson) {
      let rawData = JSON.parse(this.dragonBonesJson);
      this._uuid = rawData.name;
    }

    let armatureKey = this._uuid + "#" + atlasUUID;

    let dragonBonesData = this._factory.getDragonBonesData(armatureKey);

    if (dragonBonesData) return armatureKey;
    let filePath = null;

    if (this.dragonBonesJson) {
      filePath = this.dragonBonesJson;
    } else {
      filePath = cacheManager.getCache(this.nativeUrl) || this.nativeUrl;
    }

    this._factory.parseDragonBonesDataByPath(filePath, armatureKey);

    return armatureKey;
  };

  let armatureCacheMgr = dragonBones.ArmatureCacheMgr.getInstance();
  dragonBones.armatureCacheMgr = armatureCacheMgr;

  dbAsset._clear = function () {
    if (this._factory) {
      this._factory.removeDragonBonesDataByUUID(this._uuid, true);
    }

    armatureCacheMgr.removeArmatureCache(this._uuid);
  }; ////////////////////////////////////////////////////////////
  // override ArmatureDisplay
  ////////////////////////////////////////////////////////////


  let superProto = cc.internal.Renderable2D.prototype;
  let armatureDisplayProto = cc.internal.ArmatureDisplay.prototype;
  const AnimationCacheMode = cc.internal.ArmatureDisplay.AnimationCacheMode;

  armatureDisplayProto.initFactory = function () {
    this._factory = dragonBones.CCFactory.getFactory();
  };

  Object.defineProperty(armatureDisplayProto, 'armatureName', {
    get() {
      return this._armatureName;
    },

    set(value) {
      this._armatureName = value;
      let animNames = this.getAnimationNames(this._armatureName);

      if (!this.animationName || animNames.indexOf(this.animationName) < 0) {
        this.animationName = '';
      }

      var oldArmature = this._armature;

      if (this._armature) {
        if (!this.isAnimationCached()) {
          this._factory.remove(this._armature);
        }

        this._armature = null;
      }

      this._nativeDisplay = null;

      this._refresh();

      if (oldArmature && oldArmature != this._armature) {
        oldArmature.dispose();
      }

      if (this._armature && !this.isAnimationCached()) {
        this._factory.add(this._armature);
      }
    },

    visible: false
  });
  Object.defineProperty(armatureDisplayProto, "premultipliedAlpha", {
    get() {
      if (this._premultipliedAlpha === undefined) {
        return false;
      }

      return this._premultipliedAlpha;
    },

    set(value) {
      this._premultipliedAlpha = value;

      if (this._nativeDisplay) {
        this._nativeDisplay.setOpacityModifyRGB(this._premultipliedAlpha);
      }
    }

  });
  let _initDebugDraw = armatureDisplayProto._initDebugDraw;

  armatureDisplayProto._initDebugDraw = function () {
    _initDebugDraw.call(this);

    if (this._armature && !this.isAnimationCached()) {
      this._nativeDisplay.setDebugBonesEnabled(this.debugBones);
    }
  };

  armatureDisplayProto._buildArmature = function () {
    if (!this.dragonAsset || !this.dragonAtlasAsset || !this.armatureName) {
      return;
    }

    if (this._nativeDisplay) {
      this._nativeDisplay.dispose();

      this._nativeDisplay._comp = null;
      this._nativeDisplay = null;
    }

    let atlasUUID = this.dragonAtlasAsset._uuid;
    this._armatureKey = this.dragonAsset.init(this._factory, atlasUUID);

    if (this.isAnimationCached()) {
      this._nativeDisplay = new dragonBones.CCArmatureCacheDisplay(this.armatureName, this._armatureKey, atlasUUID, this._cacheMode == AnimationCacheMode.SHARED_CACHE);
      this._armature = this._nativeDisplay.armature();
    } else {
      this._nativeDisplay = this._factory.buildArmatureDisplay(this.armatureName, this._armatureKey, "", atlasUUID);

      if (!this._nativeDisplay) {
        return;
      }

      this._nativeDisplay.setDebugBonesEnabled(this.debugBones);

      this._armature = this._nativeDisplay.armature();
      this._armature.animation.timeScale = this.timeScale;

      this._factory.add(this._armature);
    } // add all event into native display


    let callbackTable = this._eventTarget._callbackTable; // just use to adapt to native api

    let emptyHandle = function () {};

    for (let key in callbackTable) {
      let list = callbackTable[key];
      if (!list || !list.callbackInfos || !list.callbackInfos.length) continue;

      if (this.isAnimationCached()) {
        this._nativeDisplay.addDBEventListener(key);
      } else {
        this._nativeDisplay.addDBEventListener(key, emptyHandle);
      }
    }

    this._preCacheMode = this._cacheMode;
    this._nativeDisplay._ccNode = this.node;
    this._nativeDisplay._comp = this;
    this._nativeDisplay._eventTarget = this._eventTarget;
    this._sharedBufferOffset = this._nativeDisplay.getSharedBufferOffset();
    this._sharedBufferOffset[0] = 0;
    this._useAttach = false;
    this._renderOrder = -1; // store render order and world matrix

    this._paramsBuffer = this._nativeDisplay.getParamsBuffer();
    this._paramsBuffer[0] = -1.0;

    this._nativeDisplay.setOpacityModifyRGB(this.premultipliedAlpha);

    let compColor = this.color;

    this._nativeDisplay.setColor(compColor.r, compColor.g, compColor.b, compColor.a);

    this._nativeDisplay.setDBEventCallback(function (eventObject) {
      this._eventTarget.emit(eventObject.type, eventObject);
    });

    this.attachUtil.init(this);

    if (this.animationName) {
      this.playAnimation(this.animationName, this.playTimes);
    }

    this.syncTransform(true);
    this.markForUpdateRenderData();
  };

  armatureDisplayProto._updateColor = function () {
    if (this._nativeDisplay) {
      let compColor = this.color;

      this._nativeDisplay.setColor(compColor.r, compColor.g, compColor.b, compColor.a);
    }
  };

  armatureDisplayProto.playAnimation = function (animName, playTimes) {
    this.playTimes = playTimes === undefined ? -1 : playTimes;
    this.animationName = animName;

    if (this._nativeDisplay) {
      if (this.isAnimationCached()) {
        return this._nativeDisplay.playAnimation(animName, this.playTimes);
      } else {
        if (this._armature) {
          return this._armature.animation.play(animName, this.playTimes);
        }
      }
    }

    return null;
  };

  armatureDisplayProto.updateAnimationCache = function (animName) {
    if (!this.isAnimationCached()) return;

    if (this._nativeDisplay) {
      if (animName) {
        this._nativeDisplay.updateAnimationCache(animName);
      } else {
        this._nativeDisplay.updateAllAnimationCache();
      }
    }
  };

  armatureDisplayProto.invalidAnimationCache = function () {
    if (!this.isAnimationCached()) return;

    if (this._nativeDisplay) {
      this._nativeDisplay.updateAllAnimationCache();
    }
  };

  let _onEnable = superProto.onEnable;

  armatureDisplayProto.onEnable = function () {
    _onEnable.call(this);

    if (this._armature && !this.isAnimationCached()) {
      this._factory.add(this._armature);
    }

    this._onSyncTransform();

    this.syncTransform(true);

    this._flushAssembler();

    middleware.retain();
  };

  let _onDisable = superProto.onDisable;

  armatureDisplayProto.onDisable = function () {
    _onDisable.call(this);

    if (this._armature && !this.isAnimationCached()) {
      this._factory.remove(this._armature);
    }

    this._offSyncTransform();

    middleware.release();
  };

  armatureDisplayProto.once = function (eventType, listener, target) {
    if (this._nativeDisplay) {
      if (this.isAnimationCached()) {
        this._nativeDisplay.addDBEventListener(eventType);
      } else {
        this._nativeDisplay.addDBEventListener(eventType, listener);
      }
    }

    this._eventTarget.once(eventType, listener, target);
  };

  armatureDisplayProto.addEventListener = function (eventType, listener, target) {
    if (this._nativeDisplay) {
      if (this.isAnimationCached()) {
        this._nativeDisplay.addDBEventListener(eventType);
      } else {
        this._nativeDisplay.addDBEventListener(eventType, listener);
      }
    }

    this._eventTarget.on(eventType, listener, target);
  };

  armatureDisplayProto.removeEventListener = function (eventType, listener, target) {
    if (this._nativeDisplay) {
      if (this.isAnimationCached()) {
        this._nativeDisplay.removeDBEventListener(eventType);
      } else {
        this._nativeDisplay.removeDBEventListener(eventType, listener);
      }
    }

    this._eventTarget.off(eventType, listener, target);
  };

  let _onDestroy = armatureDisplayProto.onDestroy;

  armatureDisplayProto.onDestroy = function () {
    _onDestroy.call(this);

    if (this._nativeDisplay) {
      this._nativeDisplay.dispose();

      this._nativeDisplay._comp = null;
      this._nativeDisplay = null;
    }
  };

  armatureDisplayProto.syncTransform = function (force) {
    let node = this.node;
    if (!node) return;
    let paramsBuffer = this._paramsBuffer;
    if (!paramsBuffer) return; // sync node world matrix to native

    node.updateWorldTransform();
    let worldMat = node._mat;
    paramsBuffer[1] = worldMat.m00;
    paramsBuffer[2] = worldMat.m01;
    paramsBuffer[3] = worldMat.m02;
    paramsBuffer[4] = worldMat.m03;
    paramsBuffer[5] = worldMat.m04;
    paramsBuffer[6] = worldMat.m05;
    paramsBuffer[7] = worldMat.m06;
    paramsBuffer[8] = worldMat.m07;
    paramsBuffer[9] = worldMat.m08;
    paramsBuffer[10] = worldMat.m09;
    paramsBuffer[11] = worldMat.m10;
    paramsBuffer[12] = worldMat.m11;
    paramsBuffer[13] = worldMat.m12;
    paramsBuffer[14] = worldMat.m13;
    paramsBuffer[15] = worldMat.m14;
    paramsBuffer[16] = worldMat.m15;
  };

  armatureDisplayProto.setAnimationCacheMode = function (cacheMode) {
    if (this._preCacheMode !== cacheMode) {
      this._cacheMode = cacheMode;

      this._buildArmature();

      if (this._armature && !this.isAnimationCached()) {
        this._factory.add(this._armature);
      }

      this._updateSocketBindings();

      this.markForUpdateRenderData();
    }
  };

  armatureDisplayProto.update = function () {
    let nativeDisplay = this._nativeDisplay;
    if (!nativeDisplay) return;
    let node = this.node;
    if (!node) return;
    let paramsBuffer = this._paramsBuffer;

    if (this._renderOrder != middleware.renderOrder) {
      paramsBuffer[0] = middleware.renderOrder;
      this._renderOrder = middleware.renderOrder;
      middleware.renderOrder++;
    }

    if (this.__preColor__ === undefined || !this.color.equals(this.__preColor__)) {
      let compColor = this.color;
      nativeDisplay.setColor(compColor.r, compColor.g, compColor.b, compColor.a);
      this.__preColor__ = compColor;
    }

    const socketNodes = this.socketNodes;

    if (!this._useAttach && socketNodes.size > 0) {
      this._useAttach = true;
      nativeDisplay.setAttachEnabled(true);
    }

    this.markForUpdateRenderData();

    if (!this.isAnimationCached() && this._debugDraw && this.debugBones) {
      let nativeDisplay = this._nativeDisplay;
      this._debugData = this._debugData || nativeDisplay.getDebugData();
      if (!this._debugData) return;
      let graphics = this._debugDraw;
      graphics.clear();
      let debugData = this._debugData;
      let debugIdx = 0;
      graphics.lineWidth = 5;
      graphics.strokeColor = _boneColor;
      graphics.fillColor = _slotColor; // Root bone color is same as slot color.

      let debugBonesLen = debugData[debugIdx++];

      for (let i = 0; i < debugBonesLen; i += 4) {
        let bx = debugData[debugIdx++];
        let by = debugData[debugIdx++];
        let x = debugData[debugIdx++];
        let y = debugData[debugIdx++]; // Bone lengths.

        graphics.moveTo(bx, by);
        graphics.lineTo(x, y);
        graphics.stroke(); // Bone origins.

        graphics.circle(bx, by, Math.PI * 2);
        graphics.fill();

        if (i === 0) {
          graphics.fillColor = _originColor;
        }
      }
    }
  };

  let _tempAttachMat4 = new cc.mat4();

  let _tempBufferIndex, _tempIndicesOffset, _tempIndicesCount;

  armatureDisplayProto._render = function (ui) {
    let nativeDisplay = this._nativeDisplay;
    if (!nativeDisplay) return;
    let node = this.node;
    if (!node) return;
    let sharedBufferOffset = this._sharedBufferOffset;
    if (!sharedBufferOffset) return;
    let renderInfoOffset = sharedBufferOffset[0]; // reset render info offset

    sharedBufferOffset[0] = 0;
    const sockets = this.sockets;

    if (sockets.length > 0) {
      let attachInfoMgr = middleware.attachInfoMgr;
      let attachInfo = attachInfoMgr.attachInfo;
      let attachInfoOffset = sharedBufferOffset[1]; // reset attach info offset

      sharedBufferOffset[1] = 0;
      const socketNodes = this.socketNodes;
      const scale = new cc.Vec3();

      const bones = this._armature.getBones();

      for (let l = sockets.length - 1; l >= 0; l--) {
        const sock = sockets[l];
        const boneNode = sock.target;
        const boneIdx = sock.boneIndex;
        if (!boneNode) continue; // Node has been destroy

        if (!boneNode.isValid) {
          socketNodes.delete(sock.path);
          sockets.splice(l, 1);
          continue;
        }

        let tm = _tempAttachMat4;
        let matOffset = attachInfoOffset + boneIdx * 16;
        tm.m00 = attachInfo[matOffset];
        tm.m01 = attachInfo[matOffset + 1];
        tm.m04 = attachInfo[matOffset + 4];
        tm.m05 = attachInfo[matOffset + 5];
        tm.m12 = attachInfo[matOffset + 12];
        tm.m13 = attachInfo[matOffset + 13];

        if (!boneNode._oldScale) {
          // back origin scale info
          boneNode._oldScale = boneNode.scale.clone();
        }

        scale.set(boneNode._oldScale);
        boneNode.matrix = tm;
        boneNode.scale = scale.multiply(node.scale);
      }
    }

    let renderInfoMgr = middleware.renderInfoMgr;
    let renderInfo = renderInfoMgr.renderInfo;
    let materialIdx = 0,
        realTextureIndex,
        realTexture; // verify render border

    let border = renderInfo[renderInfoOffset + materialIdx++];
    if (border !== 0xffffffff) return;
    let matLen = renderInfo[renderInfoOffset + materialIdx++];
    if (matLen == 0) return;

    for (let index = 0; index < matLen; index++) {
      realTextureIndex = renderInfo[renderInfoOffset + materialIdx++];
      realTexture = this.dragonAtlasAsset.getTextureByIndex(realTextureIndex);
      if (!realTexture) return; // SpineMaterialType.TWO_COLORED 2
      // SpineMaterialType.COLORED_TEXTURED 0
      // cache material

      this.material = this.getMaterialForBlend(renderInfo[renderInfoOffset + materialIdx++], renderInfo[renderInfoOffset + materialIdx++]);
      _tempBufferIndex = renderInfo[renderInfoOffset + materialIdx++];
      _tempIndicesOffset = renderInfo[renderInfoOffset + materialIdx++];
      _tempIndicesCount = renderInfo[renderInfoOffset + materialIdx++];

      if (middleware.indicesStart != _tempIndicesOffset || middleware.preRenderBufferIndex != _tempBufferIndex || middleware.preRenderBufferType != middleware.vfmtPosUvColor) {
        ui.autoMergeBatches(middleware.preRenderComponent);
        middleware.resetIndicesStart = true;
      } else {
        middleware.resetIndicesStart = false;
      }

      ui.commitComp(this, realTexture._texture, this._assembler, null);
    }
  }; //////////////////////////////////////////
  // assembler


  const assembler = cc.internal.DragonBonesAssembler;

  assembler.updateRenderData = function () {};

  assembler.fillBuffers = function (comp, renderer) {
    let nativeDisplay = comp._nativeDisplay;
    if (!nativeDisplay) return;
    let node = comp.node;
    if (!node) return;
    let renderInfoLookup = middleware.RenderInfoLookup;
    let buffer = renderInfoLookup[middleware.vfmtPosUvColor][_tempBufferIndex];
    renderer.currBufferBatch = buffer;

    if (middleware.resetIndicesStart) {
      buffer.indicesStart = _tempIndicesOffset;
    }

    buffer.indicesOffset = _tempIndicesOffset + _tempIndicesCount;
    middleware.indicesStart = buffer.indicesOffset;
    middleware.preRenderComponent = comp;
    middleware.preRenderBufferIndex = _tempBufferIndex;
    middleware.preRenderBufferType = middleware.vfmtPosUvColor;
  };
})();

},{"./jsb-cache-manager":4}],6:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
(function () {
  if (!(cc && cc.EditBoxComponent)) {
    return;
  }

  const EditBox = cc.EditBoxComponent;
  const KeyboardReturnType = EditBox.KeyboardReturnType;
  const InputMode = EditBox.InputMode;
  const InputFlag = EditBox.InputFlag;
  let worldMat = cc.mat4();

  function getInputType(type) {
    switch (type) {
      case InputMode.EMAIL_ADDR:
        return 'email';

      case InputMode.NUMERIC:
      case InputMode.DECIMAL:
        return 'number';

      case InputMode.PHONE_NUMBER:
        return 'phone';

      case InputMode.URL:
        return 'url';

      case InputMode.SINGLE_LINE:
      case InputMode.ANY:
      default:
        return 'text';
    }
  }

  function getKeyboardReturnType(type) {
    switch (type) {
      case KeyboardReturnType.DEFAULT:
      case KeyboardReturnType.DONE:
        return 'done';

      case KeyboardReturnType.SEND:
        return 'send';

      case KeyboardReturnType.SEARCH:
        return 'search';

      case KeyboardReturnType.GO:
        return 'go';

      case KeyboardReturnType.NEXT:
        return 'next';
    }

    return 'done';
  }

  const BaseClass = EditBox._EditBoxImpl;

  class JsbEditBoxImpl extends BaseClass {
    init(delegate) {
      if (!delegate) {
        cc.error('EditBox init failed');
        return;
      }

      this._delegate = delegate;
    }

    beginEditing() {
      let self = this;
      let delegate = this._delegate;
      let multiline = delegate.inputMode === InputMode.ANY;

      let rect = this._getRect();

      this.setMaxLength(delegate.maxLength);
      let inputTypeString = getInputType(delegate.inputMode);

      if (delegate.inputFlag === InputFlag.PASSWORD) {
        inputTypeString = 'password';
      }

      function onConfirm(res) {
        delegate._editBoxEditingReturn();
      }

      function onInput(res) {
        if (res.value.length > self._maxLength) {
          res.value = res.value.slice(0, self._maxLength);
        }

        if (delegate.string !== res.value) {
          delegate._editBoxTextChanged(res.value);
        }
      }

      function onComplete(res) {
        self.endEditing();
      }

      jsb.inputBox.onInput(onInput);
      jsb.inputBox.onConfirm(onConfirm);
      jsb.inputBox.onComplete(onComplete);

      if (!cc.sys.isMobile) {
        delegate._hideLabels();
      }

      jsb.inputBox.show({
        defaultValue: delegate.string,
        maxLength: self._maxLength,
        multiple: multiline,
        confirmHold: false,
        confirmType: getKeyboardReturnType(delegate.returnType),
        inputType: inputTypeString,
        originX: rect.x,
        originY: rect.y,
        width: rect.width,
        height: rect.height
      });
      this._editing = true;

      delegate._editBoxEditingDidBegan();
    }

    endEditing() {
      this._editing = false;

      if (!cc.sys.isMobile) {
        this._delegate._showLabels();
      }

      jsb.inputBox.offConfirm();
      jsb.inputBox.offInput();
      jsb.inputBox.offComplete();
      jsb.inputBox.hide();

      this._delegate._editBoxEditingDidEnded();
    }

    setMaxLength(maxLength) {
      if (!isNaN(maxLength)) {
        if (maxLength < 0) {
          //we can't set Number.MAX_VALUE to input's maxLength property
          //so we use a magic number here, it should works at most use cases.
          maxLength = 65535;
        }

        this._maxLength = maxLength;
      }
    }

    _getRect() {
      let node = this._delegate.node;
      let viewScaleX = cc.view._scaleX;
      let viewScaleY = cc.view._scaleY;
      let dpr = cc.view._devicePixelRatio;
      node.getWorldMatrix(worldMat);
      let transform = node._uiProps.uiTransformComp;
      let vec3 = cc.v3();
      let width = 0;
      let height = 0;

      if (transform) {
        const contentSize = transform.contentSize;
        const anchorPoint = transform.anchorPoint;
        width = contentSize.width;
        height = contentSize.height;
        vec3.x = -anchorPoint.x * width;
        vec3.y = -anchorPoint.y * height;
      }

      cc.Mat4.translate(worldMat, worldMat, vec3);
      viewScaleX /= dpr;
      viewScaleY /= dpr;
      let finalScaleX = worldMat.m00 * viewScaleX;
      let finaleScaleY = worldMat.m05 * viewScaleY;
      let viewportRect = cc.view._viewportRect;
      let offsetX = viewportRect.x / dpr,
          offsetY = viewportRect.y / dpr;
      return {
        x: worldMat.m12 * viewScaleX + offsetX,
        y: worldMat.m13 * viewScaleY + offsetY,
        width: width * finalScaleX,
        height: height * finaleScaleY
      };
    }

  }

  EditBox._EditBoxImpl = JsbEditBoxImpl;
})();

},{}],7:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
(function () {
  if (!window.middleware) return;
  let middlewareMgr = middleware.MiddlewareManager.getInstance();
  let reference = 0;
  let director = cc.director;
  let nativeXYZUVC = middleware.vfmtPosUvColor = 9;
  let nativeXYZUVCC = middleware.vfmtPosUvTwoColor = 13;
  let bytesXYZUVC = nativeXYZUVC * 4;
  let bytesXYZUVCC = nativeXYZUVCC * 4;
  let vfmtPosUvColor = cc.internal.vfmtPosUvColor;
  let vfmtPosUvTwoColor = cc.internal.vfmtPosUvTwoColor;
  let renderInfoLookup = middleware.RenderInfoLookup = {};
  renderInfoLookup[nativeXYZUVC] = [];
  renderInfoLookup[nativeXYZUVCC] = [];
  middleware.preRenderComponent = null;
  middleware.preRenderBufferIndex = 0;
  middleware.preRenderBufferType = nativeXYZUVC;
  middleware.renderOrder = 0;
  middleware.indicesStart = 0;
  middleware.resetIndicesStart = false;

  middleware.retain = function () {
    reference++;
  };

  middleware.release = function () {
    if (reference === 0) {
      cc.warn("middleware reference error: reference count should be greater than 0");
      return;
    }

    reference--;

    if (reference === 0) {
      const batcher2D = director.root.batcher2D;
      const uvcBuffers = renderInfoLookup[nativeXYZUVC];

      for (let i = 0; i < uvcBuffers.length; i++) {
        batcher2D.unRegisterCustomBuffer(uvcBuffers[i]);
        uvcBuffers[i].destroy();
      }

      uvcBuffers.length = 0;
      const uvccBuffers = renderInfoLookup[nativeXYZUVCC];

      for (let i = 0; i < uvccBuffers.length; i++) {
        batcher2D.unRegisterCustomBuffer(uvccBuffers[i]);
        uvccBuffers[i].destroy();
      }

      uvccBuffers.length = 0;
    }
  };

  function CopyNativeBufferToJS(renderer, nativeFormat, jsFormat) {
    if (!renderer) return;
    let bufferCount = middlewareMgr.getBufferCount(nativeFormat);

    for (let i = 0; i < bufferCount; i++) {
      let ibBytesLength = middlewareMgr.getIBTypedArrayLength(nativeFormat, i);
      let srcVertexCount = 65535;
      let srcIndicesCount = ibBytesLength / 2; // USHORT

      let srcVertexFloatCount = srcVertexCount * nativeFormat;
      let buffer = renderInfoLookup[nativeFormat][i];

      if (!buffer) {
        buffer = renderer.registerCustomBuffer(jsFormat);
      }

      buffer.reset();
      const isRecreate = buffer.request(srcVertexCount, srcIndicesCount);

      if (!isRecreate) {
        buffer = renderer.registerCustomBuffer(jsFormat);
      }

      const vBuf = buffer.vData;
      const iBuf = buffer.iData;
      const srcVBuf = middlewareMgr.getVBTypedArray(nativeFormat, i);
      const srcIBuf = middlewareMgr.getIBTypedArray(nativeFormat, i);
      vBuf.set(srcVBuf.subarray(0, srcVertexFloatCount), 0);
      iBuf.set(srcIBuf.subarray(0, srcIndicesCount), 0); // forbid js upload data, call by middleware

      buffer.uploadBuffers(); // forbid auto merge, because of it's meanless

      buffer.indicesOffset = 0;
      renderInfoLookup[nativeFormat][i] = buffer;
    }
  }

  director.on(cc.Director.EVENT_BEFORE_UPDATE, function () {
    if (reference === 0) return;
    middlewareMgr.update(director._deltaTime);
  });
  director.on(cc.Director.EVENT_BEFORE_DRAW, function () {
    if (reference === 0) return;
    middlewareMgr.render(director._deltaTime); // reset render order

    middleware.renderOrder = 0;
    middleware.preRenderComponent = null;
    middleware.preRenderBufferIndex = 0;
    middleware.preRenderBufferType = nativeXYZUVC;
    middleware.indicesStart = 0;
    middleware.resetIndicesStart = false;
    let batcher2D = director.root.batcher2D;
    CopyNativeBufferToJS(batcher2D, nativeXYZUVC, vfmtPosUvColor);
    CopyNativeBufferToJS(batcher2D, nativeXYZUVCC, vfmtPosUvTwoColor);
  });
  let renderInfoMgr = middlewareMgr.getRenderInfoMgr();
  renderInfoMgr.renderInfo = renderInfoMgr.getSharedBuffer();
  renderInfoMgr.setResizeCallback(function () {
    this.attachInfo = this.getSharedBuffer();
  });
  renderInfoMgr.__middleware__ = middleware;
  let attachInfoMgr = middlewareMgr.getAttachInfoMgr();
  attachInfoMgr.attachInfo = attachInfoMgr.getSharedBuffer();
  attachInfoMgr.setResizeCallback(function () {
    this.attachInfo = this.getSharedBuffer();
  });
  middleware.renderInfoMgr = renderInfoMgr;
  middleware.attachInfoMgr = attachInfoMgr; // generate get set function

  middleware.generateGetSet = function (moduleObj) {
    for (let classKey in moduleObj) {
      let classProto = moduleObj[classKey] && moduleObj[classKey].prototype;
      if (!classProto) continue;

      for (let getName in classProto) {
        let getPos = getName.search(/^get/);
        if (getPos == -1) continue;
        let propName = getName.replace(/^get/, '');
        let nameArr = propName.split('');
        let lowerFirst = nameArr[0].toLowerCase();
        let upperFirst = nameArr[0].toUpperCase();
        nameArr.splice(0, 1);
        let left = nameArr.join('');
        propName = lowerFirst + left;
        let setName = 'set' + upperFirst + left;
        if (classProto.hasOwnProperty(propName)) continue;
        let setFunc = classProto[setName];
        let hasSetFunc = typeof setFunc === 'function';

        if (hasSetFunc) {
          Object.defineProperty(classProto, propName, {
            get() {
              return this[getName]();
            },

            set(val) {
              this[setName](val);
            },

            configurable: true
          });
        } else {
          Object.defineProperty(classProto, propName, {
            get() {
              return this[getName]();
            },

            configurable: true
          });
        }
      }
    }
  };
})();

},{}],8:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2017-2020 Xiamen Yaji Software Co., Ltd.
 https://www.cocos.com/
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of fsUtils software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.
 The software or tools in fsUtils License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
var fs = jsb.fileUtils;
let jsb_downloader = null;
let downloading = new cc.AssetManager.Cache();
let tempDir = '';
var fsUtils = {
  fs,

  initJsbDownloader(jsbDownloaderMaxTasks, jsbDownloaderTimeout) {
    jsb_downloader = new jsb.Downloader({
      countOfMaxProcessingTasks: jsbDownloaderMaxTasks || 32,
      timeoutInSeconds: jsbDownloaderTimeout || 30,
      tempFileNameSuffix: '.tmp'
    });
    tempDir = fsUtils.getUserDataPath() + '/temp';
    !fs.isDirectoryExist(tempDir) && fs.createDirectory(tempDir);
    jsb_downloader.setOnFileTaskSuccess(task => {
      if (!downloading.has(task.requestURL)) return;
      let {
        onComplete
      } = downloading.remove(task.requestURL);
      onComplete && onComplete(null, task.storagePath);
    });
    jsb_downloader.setOnTaskError((task, errorCode, errorCodeInternal, errorStr) => {
      if (!downloading.has(task.requestURL)) return;
      let {
        onComplete
      } = downloading.remove(task.requestURL);
      cc.error(`Download file failed: path: ${task.requestURL} message: ${errorStr}, ${errorCode}`);
      onComplete(new Error(errorStr), null);
    });
    jsb_downloader.setOnTaskProgress((task, bytesReceived, totalBytesReceived, totalBytesExpected) => {
      if (!downloading.has(task.requestURL)) return;
      let {
        onProgress
      } = downloading.get(task.requestURL);
      onProgress && onProgress(totalBytesReceived, totalBytesExpected);
    });
  },

  getUserDataPath() {
    return fs.getWritablePath().replace(/[\/\\]*$/, '');
  },

  checkFsValid() {
    if (!fs) {
      cc.warn('can not get the file system!');
      return false;
    }

    return true;
  },

  deleteFile(filePath, onComplete) {
    var result = fs.removeFile(filePath);

    if (result === true) {
      onComplete && onComplete(null);
    } else {
      cc.warn(`Delete file failed: path: ${filePath}`);
      onComplete && onComplete(new Error('delete file failed'));
    }
  },

  downloadFile(remoteUrl, filePath, header, onProgress, onComplete) {
    downloading.add(remoteUrl, {
      onProgress,
      onComplete
    });
    var storagePath = filePath;
    if (!storagePath) storagePath = tempDir + '/' + performance.now() + cc.path.extname(remoteUrl);
    jsb_downloader.createDownloadFileTask(remoteUrl, storagePath, header);
  },

  saveFile(srcPath, destPath, onComplete) {
    var err = null;
    let result = fs.writeDataToFile(fs.getDataFromFile(srcPath), destPath);
    fs.removeFile(srcPath);

    if (!result) {
      err = new Error(`Save file failed: path: ${srcPath}`);
      cc.warn(err.message);
    }

    onComplete && onComplete(err);
  },

  copyFile(srcPath, destPath, onComplete) {
    var err = null;
    let result = fs.writeDataToFile(fs.getDataFromFile(srcPath), destPath);

    if (!result) {
      err = new Error(`Copy file failed: path: ${srcPath}`);
      cc.warn(err.message);
    }

    onComplete && onComplete(err);
  },

  writeFile(path, data, encoding, onComplete) {
    var result = null;
    var err = null;

    if (encoding === 'utf-8' || encoding === 'utf8') {
      result = fs.writeStringToFile(data, path);
    } else {
      result = fs.writeDataToFile(data, path);
    }

    if (!result) {
      err = new Error(`Write file failed: path: ${path}`);
      cc.warn(err.message);
    }

    onComplete && onComplete(err);
  },

  writeFileSync(path, data, encoding) {
    var result = null;

    if (encoding === 'utf-8' || encoding === 'utf8') {
      result = fs.writeStringToFile(data, path);
    } else {
      result = fs.writeDataToFile(data, path);
    }

    if (!result) {
      cc.warn(`Write file failed: path: ${path}`);
      return new Error(`Write file failed: path: ${path}`);
    }
  },

  readFile(filePath, encoding, onComplete) {
    var content = null,
        err = null;

    if (encoding === 'utf-8' || encoding === 'utf8') {
      content = fs.getStringFromFile(filePath);
    } else {
      content = fs.getDataFromFile(filePath);
    }

    if (!content) {
      err = new Error(`Read file failed: path: ${filePath}`);
      cc.warn(err.message);
    }

    onComplete && onComplete(err, content);
  },

  readDir(filePath, onComplete) {
    var files = null,
        err = null;

    try {
      files = fs.listFiles(filePath);
    } catch (e) {
      cc.warn(`Read dir failed: path: ${filePath} message: ${e.message}`);
      err = new Error(e.message);
    }

    onComplete && onComplete(err, files);
  },

  readText(filePath, onComplete) {
    fsUtils.readFile(filePath, 'utf8', onComplete);
  },

  readArrayBuffer(filePath, onComplete) {
    fsUtils.readFile(filePath, '', onComplete);
  },

  readJson(filePath, onComplete) {
    fsUtils.readFile(filePath, 'utf8', function (err, text) {
      var out = null;

      if (!err) {
        try {
          out = JSON.parse(text);
        } catch (e) {
          cc.warn(`Read json failed: path: ${filePath} message: ${e.message}`);
          err = new Error(e.message);
        }
      }

      onComplete && onComplete(err, out);
    });
  },

  readJsonSync(path) {
    try {
      var str = fs.getStringFromFile(path);
      return JSON.parse(str);
    } catch (e) {
      cc.warn(`Read json failed: path: ${path} message: ${e.message}`);
      return new Error(e.message);
    }
  },

  makeDirSync(path, recursive) {
    let result = fs.createDirectory(path);

    if (!result) {
      cc.warn(`Make directory failed: path: ${path}`);
      return new Error(`Make directory failed: path: ${path}`);
    }
  },

  rmdirSync(dirPath, recursive) {
    let result = fs.removeDirectory(dirPath);

    if (!result) {
      cc.warn(`rm directory failed: path: ${dirPath}`);
      return new Error(`rm directory failed: path: ${dirPath}`);
    }
  },

  exists(filePath, onComplete) {
    var result = fs.isFileExist(filePath);
    onComplete && onComplete(result);
  },

  loadSubpackage(name, onProgress, onComplete) {
    throw new Error('not implement');
  }

};
window.fsUtils = module.exports = fsUtils;

},{}],9:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
cc.game.restart = function () {
  // Need to clear scene, or native object destructor won't be invoke.
  cc.director.getScene().destroy();

  cc.Object._deferredDestroy();

  __restartVM();
};

jsb.onError(function (location, message, stack) {
  console.error(location, message, stack);
});

jsb.onPause = function () {
  cc.game.emit(cc.Game.EVENT_HIDE);
};

jsb.onResume = function () {
  cc.game.emit(cc.Game.EVENT_SHOW);
};

jsb.onResize = function (size) {
  if (size.width === 0 || size.height === 0) return;
  cc.sys.windowPixelResolution = {
    width: size.width,
    height: size.height
  };
  size.width /= window.devicePixelRatio;
  size.height /= window.devicePixelRatio;
  window.resize(size.width, size.height);
};

jsb.onOrientationChanged = function (event) {
  window.orientation = event.orientation;
  window.dispatchEvent({
    type: 'orientationchange'
  });
};

jsb.onMemoryWarning = function () {
  cc.game.emit(cc.Game.EVENT_LOW_MEMORY);
};

},{}],10:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
// Converters for converting js objects to jsb struct objects
let _converters = {
  texImagesToBuffers: function (texImages) {
    if (texImages) {
      let buffers = [];

      for (let i = 0; i < texImages.length; ++i) {
        let texImage = texImages[i];

        if (texImage instanceof HTMLCanvasElement) {
          // Refer to HTMLCanvasElement and ImageData implementation
          buffers.push(texImage._data.data);
        } else if (texImage instanceof HTMLImageElement) {
          // Refer to HTMLImageElement implementation
          buffers.push(texImage._data);
        } else {
          console.log('copyTexImagesToTexture: Convert texImages to data buffers failed');
          return null;
        }
      }

      return buffers;
    }
  },
  DeviceInfo: function (info) {
    let width = cc.game.canvas.width,
        height = cc.game.canvas.height,
        handler = window.windowHandler;
    return new gfx.DeviceInfo(handler, width, height, info.nativeWidth, info.nativeHeight, null, info.bindingMappingInfo);
  }
}; // Helper functions to convert the original jsb function to a wrapper function

function replaceFunction(jsbFunc, ...converters) {
  let l = converters.length; // Validation

  for (let i = 0; i < l; ++i) {
    if (!converters[i]) {
      return null;
    }
  }

  if (l === 1) {
    return function (param0) {
      // Convert parameters one by one
      let _jsbParam0 = converters[0](param0);

      return this[jsbFunc](_jsbParam0);
    };
  } else if (l === 2) {
    return function (param0, param1) {
      // Convert parameters one by one
      let _jsbParam0 = converters[0](param0);

      let _jsbParam1 = converters[1](param1);

      return this[jsbFunc](_jsbParam0, _jsbParam1);
    };
  } else if (l === 3) {
    return function (param0, param1, param2) {
      // Convert parameters one by one
      let _jsbParam0 = converters[0](param0);

      let _jsbParam1 = converters[1](param1);

      let _jsbParam2 = converters[2](param2);

      return this[jsbFunc](_jsbParam0, _jsbParam1, _jsbParam2);
    };
  } else {
    return function (...params) {
      if (l !== params.length) {
        throw new Error(jsbFunc + ': The parameters length don\'t match the converters length');
      }

      let jsbParams = new Array(l);

      for (let i = 0; i < l; ++i) {
        jsbParams[i] = converters[i](params[i]);
      }

      return this[jsbFunc].apply(this, jsbParams);
    };
  }

  ;
} // Replace all given functions to the wrapper function provided


function replace(proto, replacements) {
  for (let func in replacements) {
    let oldFunc = proto[func];
    let newFunc = replacements[func];

    if (oldFunc && newFunc) {
      let jsbFunc = '_' + func;
      proto[jsbFunc] = oldFunc;
      proto[func] = newFunc;
    }
  }
} // Cache dirty to avoid invoking gfx.DescriptorSet.update().


let descriptorSetProto = gfx.DescriptorSet.prototype;

descriptorSetProto.bindBuffer = function (binding, buffer, index) {
  this.dirtyJSB = descriptorSetProto.bindBufferJSB.call(this, binding, buffer, index || 0);
};

descriptorSetProto.bindSampler = function (binding, sampler, index) {
  this.dirtyJSB = descriptorSetProto.bindSamplerJSB.call(this, binding, sampler, index || 0);
};

descriptorSetProto.bindTexture = function (bindding, texture, index) {
  this.dirtyJSB = descriptorSetProto.bindTextureJSB.call(this, bindding, texture, index || 0);
};

let oldDSUpdate = descriptorSetProto.update;

descriptorSetProto.update = function () {
  if (!this.dirtyJSB) return;
  oldDSUpdate.call(this);
  this.dirtyJSB = false;
};

let deviceProtos = [gfx.CCVKDevice && gfx.CCVKDevice.prototype, gfx.CCMTLDevice && gfx.CCMTLDevice.prototype, gfx.GLES3Device && gfx.GLES3Device.prototype, gfx.GLES2Device && gfx.GLES2Device.prototype];
deviceProtos.forEach(function (item, index) {
  if (item !== undefined) {
    replace(item, {
      initialize: replaceFunction('_initialize', _converters.DeviceInfo)
    });
    let oldCopyTexImagesToTextureFunc = item.copyTexImagesToTexture;

    item.copyTexImagesToTexture = function (texImages, texture, regions) {
      let images = _converters.texImagesToBuffers(texImages);

      oldCopyTexImagesToTextureFunc.call(this, images, texture, regions);
    };

    let oldDeviceCreatBufferFun = item.createBuffer;

    item.createBuffer = function (info) {
      let buffer;

      if (info.buffer) {
        buffer = oldDeviceCreatBufferFun.call(this, info, true);
      } else {
        buffer = oldDeviceCreatBufferFun.call(this, info, false);
      }

      buffer.cachedUsage = info.usage;
      return buffer;
    };

    let oldDeviceCreatTextureFun = item.createTexture;

    item.createTexture = function (info) {
      if (info.texture) {
        return oldDeviceCreatTextureFun.call(this, info, true);
      } else {
        return oldDeviceCreatTextureFun.call(this, info, false);
      }
    };

    Object.defineProperty(item, 'uboOffsetAlignment', {
      get() {
        if (this.cachedUboOffsetAlignment === undefined) {
          this.cachedUboOffsetAlignment = this.getUboOffsetAlignment();
        }

        return this.cachedUboOffsetAlignment;
      }

    });
  }
});
let shaderProto = gfx.Shader.prototype;
cc.js.get(shaderProto, 'id', function () {
  return this.shaderID;
});
let bufferProto = gfx.Buffer.prototype;
let oldUpdate = bufferProto.update;

bufferProto.update = function (buffer, size) {
  if (buffer.byteLength === 0) return;
  let buffSize;

  if (this.cachedUsage & 0x40) {
    // BufferUsageBit.INDIRECT
    // It is a IIndirectBuffer object.
    let drawInfos = buffer.drawInfos;
    buffer = new Uint32Array(drawInfos.length * 7);
    let baseIndex = 0;
    let drawInfo;

    for (let i = 0; i < drawInfos.length; ++i) {
      baseIndex = i * 7;
      drawInfo = drawInfos[i];
      buffer[baseIndex] = drawInfo.vertexCount;
      buffer[baseIndex + 1] = drawInfo.firstVertex;
      buffer[baseIndex + 2] = drawInfo.indexCount;
      buffer[baseIndex + 3] = drawInfo.firstIndex;
      buffer[baseIndex + 4] = drawInfo.vertexOffset;
      buffer[baseIndex + 5] = drawInfo.instanceCount;
      buffer[baseIndex + 6] = drawInfo.firstInstance;
    }

    buffSize = buffer.byteLength;
  } else if (size !== undefined) {
    buffSize = size;
  } else {
    buffSize = buffer.byteLength;
  }

  oldUpdate.call(this, buffer, buffSize);
};

let oldBufferInitializeFunc = bufferProto.initialize;

bufferProto.initialize = function (info) {
  if (info.buffer) {
    oldBufferInitializeFunc.call(this, info, true);
  } else {
    oldBufferInitializeFunc.call(this, info, false);
  }
};

let textureProto = gfx.Texture.prototype;
let oldTextureInitializeFunc = textureProto.initialize;

textureProto.initialize = function (info) {
  if (info.texture) {
    oldTextureInitializeFunc.call(this, info, true);
  } else {
    oldTextureInitializeFunc.call(this, info, false);
  }
};

},{}],11:[function(require,module,exports){
/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2020 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and  non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
'use strict';

const cacheManager = require('./jsb-cache-manager');

const {
  downloadFile,
  readText,
  readArrayBuffer,
  readJson,
  getUserDataPath,
  initJsbDownloader
} = require('./jsb-fs-utils');

const REGEX = /^\w+:\/\/.*/;
const downloader = cc.assetManager.downloader;
const parser = cc.assetManager.parser;
const presets = cc.assetManager.presets;
downloader.maxConcurrency = 30;
downloader.maxRequestsPerFrame = 60;
presets['preload'].maxConcurrency = 15;
presets['preload'].maxRequestsPerFrame = 30;
presets['scene'].maxConcurrency = 32;
presets['scene'].maxRequestsPerFrame = 64;
presets['bundle'].maxConcurrency = 32;
presets['bundle'].maxRequestsPerFrame = 64;
let suffix = 0;
const failureMap = {};
const maxRetryCountFromBreakpoint = 5;
const loadedScripts = {};

function downloadScript(url, options, onComplete) {
  if (typeof options === 'function') {
    onComplete = options;
    options = null;
  }

  if (loadedScripts[url]) return onComplete && onComplete();
  download(url, function (src, options, onComplete) {
    window.require(src);

    loadedScripts[url] = true;
    onComplete && onComplete(null);
  }, options, options.onFileProgress, onComplete);
}

function download(url, func, options, onFileProgress, onComplete) {
  var result = transformUrl(url, options);

  if (result.inLocal) {
    func(result.url, options, onComplete);
  } else if (result.inCache) {
    cacheManager.updateLastTime(url);
    func(result.url, options, function (err, data) {
      if (err) {
        cacheManager.removeCache(url);
      }

      onComplete(err, data);
    });
  } else {
    var time = Date.now();
    var storagePath = '';
    var failureRecord = failureMap[url];

    if (failureRecord) {
      storagePath = failureRecord.storagePath;
    } else if (options.__cacheBundleRoot__) {
      storagePath = `${options.__cacheBundleRoot__}/${time}${suffix++}${cc.path.extname(url)}`;
    } else {
      storagePath = `${time}${suffix++}${cc.path.extname(url)}`;
    }

    downloadFile(url, `${cacheManager.cacheDir}/${storagePath}`, options.header, onFileProgress, function (err, path) {
      if (err) {
        if (failureRecord) {
          failureRecord.retryCount++;

          if (failureRecord.retryCount >= maxRetryCountFromBreakpoint) {
            delete failureMap[url];
          }
        } else {
          failureMap[url] = {
            retryCount: 0,
            storagePath
          };
        }

        onComplete(err, null);
        return;
      }

      delete failureMap[url];
      func(path, options, function (err, data) {
        if (!err) {
          cacheManager.cacheFile(url, storagePath, options.__cacheBundleRoot__);
        }

        onComplete(err, data);
      });
    });
  }
}

function transformUrl(url, options) {
  var inLocal = false;
  var inCache = false;

  if (REGEX.test(url)) {
    if (options.reload) {
      return {
        url
      };
    } else {
      var cache = cacheManager.getCache(url);

      if (cache) {
        inCache = true;
        url = cache;
      }
    }
  } else {
    inLocal = true;
  }

  return {
    url,
    inLocal,
    inCache
  };
}

function doNothing(content, options, onComplete) {
  onComplete(null, content);
}

function downloadAsset(url, options, onComplete) {
  download(url, doNothing, options, options.onFileProgress, onComplete);
}

function _getFontFamily(fontHandle) {
  var ttfIndex = fontHandle.lastIndexOf(".ttf");
  if (ttfIndex === -1) return fontHandle;
  var slashPos = fontHandle.lastIndexOf("/");
  var fontFamilyName;

  if (slashPos === -1) {
    fontFamilyName = fontHandle.substring(0, ttfIndex) + "_LABEL";
  } else {
    fontFamilyName = fontHandle.substring(slashPos + 1, ttfIndex) + "_LABEL";
  }

  if (fontFamilyName.indexOf(' ') !== -1) {
    fontFamilyName = '"' + fontFamilyName + '"';
  }

  return fontFamilyName;
}

function parseText(url, options, onComplete) {
  readText(url, onComplete);
}

function parseJson(url, options, onComplete) {
  readJson(url, onComplete);
}

function downloadText(url, options, onComplete) {
  download(url, parseText, options, options.onFileProgress, onComplete);
}

function parseArrayBuffer(url, options, onComplete) {
  readArrayBuffer(url, onComplete);
}

function downloadJson(url, options, onComplete) {
  download(url, parseJson, options, options.onFileProgress, onComplete);
}

function downloadBundle(nameOrUrl, options, onComplete) {
  let bundleName = cc.path.basename(nameOrUrl);
  var version = options.version || downloader.bundleVers[bundleName];
  let url;

  if (REGEX.test(nameOrUrl) || nameOrUrl.startsWith(getUserDataPath())) {
    url = nameOrUrl;
    cacheManager.makeBundleFolder(bundleName);
  } else {
    if (downloader.remoteBundles.indexOf(bundleName) !== -1) {
      url = `${downloader.remoteServerAddress}remote/${bundleName}`;
      cacheManager.makeBundleFolder(bundleName);
    } else {
      url = `assets/${bundleName}`;
    }
  }

  var config = `${url}/cc-config.${version ? version + '.' : ''}json`;
  options.__cacheBundleRoot__ = bundleName;
  downloadJson(config, options, function (err, response) {
    if (err) {
      return onComplete(err, null);
    }

    let out = response;
    out && (out.base = url + '/');
    var js = `${url}/index.${version ? version + '.' : ''}${out.encrypted ? 'jsc' : `js`}`;
    downloadScript(js, options, function (err) {
      if (err) {
        return onComplete(err, null);
      }

      downloader.importBundleEntry(bundleName).then(function () {
        onComplete(null, out);
      }).catch(function (err) {
        onComplete(err);
      });
    });
  });
}

;

function loadFont(url, options, onComplete) {
  let fontFamilyName = _getFontFamily(url);

  let fontFace = new FontFace(fontFamilyName, "url('" + url + "')");
  document.fonts.add(fontFace);
  fontFace.load();
  fontFace.loaded.then(function () {
    onComplete(null, fontFamilyName);
  }, function () {
    cc.warnID(4933, fontFamilyName);
    onComplete(null, fontFamilyName);
  });
}

const originParsePlist = parser.parsePlist;

let parsePlist = function (url, options, onComplete) {
  readText(url, function (err, file) {
    if (err) return onComplete(err);
    originParsePlist(file, options, onComplete);
  });
};

parser.parsePVRTex = downloader.downloadDomImage;
parser.parsePKMTex = downloader.downloadDomImage;
parser.parseASTCTex = downloader.downloadDomImage;
parser.parsePlist = parsePlist;
downloader.downloadScript = downloadScript;
downloader.register({
  // JS
  '.js': downloadScript,
  '.jsc': downloadScript,
  // Images
  '.png': downloadAsset,
  '.jpg': downloadAsset,
  '.bmp': downloadAsset,
  '.jpeg': downloadAsset,
  '.gif': downloadAsset,
  '.ico': downloadAsset,
  '.tiff': downloadAsset,
  '.webp': downloadAsset,
  '.image': downloadAsset,
  '.pvr': downloadAsset,
  '.pkm': downloadAsset,
  '.astc': downloadAsset,
  // Audio
  '.mp3': downloadAsset,
  '.ogg': downloadAsset,
  '.wav': downloadAsset,
  '.m4a': downloadAsset,
  // Video
  '.mp4': downloadAsset,
  '.avi': downloadAsset,
  '.mov': downloadAsset,
  '.mpg': downloadAsset,
  '.mpeg': downloadAsset,
  '.rm': downloadAsset,
  '.rmvb': downloadAsset,
  // Text
  '.txt': downloadAsset,
  '.xml': downloadAsset,
  '.vsh': downloadAsset,
  '.fsh': downloadAsset,
  '.atlas': downloadAsset,
  '.tmx': downloadAsset,
  '.tsx': downloadAsset,
  '.fnt': downloadAsset,
  '.plist': downloadAsset,
  '.json': downloadJson,
  '.ExportJson': downloadAsset,
  '.binary': downloadAsset,
  '.bin': downloadAsset,
  '.dbbin': downloadAsset,
  '.skel': downloadAsset,
  // Font
  '.font': downloadAsset,
  '.eot': downloadAsset,
  '.ttf': downloadAsset,
  '.woff': downloadAsset,
  '.svg': downloadAsset,
  '.ttc': downloadAsset,
  'bundle': downloadBundle,
  'default': downloadText
});
parser.register({
  // Images
  '.png': downloader.downloadDomImage,
  '.jpg': downloader.downloadDomImage,
  '.bmp': downloader.downloadDomImage,
  '.jpeg': downloader.downloadDomImage,
  '.gif': downloader.downloadDomImage,
  '.ico': downloader.downloadDomImage,
  '.tiff': downloader.downloadDomImage,
  '.webp': downloader.downloadDomImage,
  '.image': downloader.downloadDomImage,
  // compressed texture
  '.pvr': downloader.downloadDomImage,
  '.pkm': downloader.downloadDomImage,
  '.astc': downloader.downloadDomImage,
  '.binary': parseArrayBuffer,
  '.bin': parseArrayBuffer,
  '.dbbin': parseArrayBuffer,
  '.skel': parseArrayBuffer,
  // Text
  '.txt': parseText,
  '.xml': parseText,
  '.vsh': parseText,
  '.fsh': parseText,
  '.atlas': parseText,
  '.tmx': parseText,
  '.tsx': parseText,
  '.fnt': parseText,
  '.plist': parsePlist,
  // Font
  '.font': loadFont,
  '.eot': loadFont,
  '.ttf': loadFont,
  '.woff': loadFont,
  '.svg': loadFont,
  '.ttc': loadFont,
  '.ExportJson': parseJson
});
cc.assetManager.transformPipeline.append(function (task) {
  var input = task.output = task.input;

  for (var i = 0, l = input.length; i < l; i++) {
    var item = input[i];

    if (item.config) {
      item.options.__cacheBundleRoot__ = item.config.name;
    }
  }
});
var originInit = cc.assetManager.init;

cc.assetManager.init = function (options) {
  originInit.call(cc.assetManager, options);
  initJsbDownloader(options.jsbDownloaderMaxTasks, options.jsbDownloaderTimeout);
  cacheManager.init();
};

},{"./jsb-cache-manager":4,"./jsb-fs-utils":8}],12:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You
 shall not use Cocos Creator software for developing other software or tools
 that's used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to
 you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
(function () {
  if (cc.ForwardPipeline) return;

  class ForwardPipeline extends nr.ForwardPipeline {
    constructor() {
      super();
      this._tag = 0;
      this._flows = [];
      this.renderTextures = [];
      this.materials = [];
    }

    destroy() {
      this.fog.destroy();
      this.ambient.destroy();
      this.skybox.destroy();
      this.shadows.destroy();
    }

    render(cameras) {
      let handles = [];

      for (let i = 0, len = cameras.length; i < len; ++i) {
        handles.push(cameras[i].handle);
      }

      super.render(handles);
    }

    init() {
      this.fog = new cc.Fog();
      this.ambient = new cc.Ambient();
      this.skybox = new cc.Skybox();
      this.shadows = new cc.Shadows();
      this.setFog(this.fog.handle);
      this.setAmbient(this.ambient.handle);
      this.setSkybox(this.skybox.handle);
      this.setShadows(this.shadows.handle);

      for (let i = 0; i < this._flows.length; i++) {
        this._flows[i].init();
      }

      let info = new nr.RenderPipelineInfo(this._tag, this._flows);
      this.initialize(info);
    }

  } // hook to invoke init after deserialization


  ForwardPipeline.prototype.onAfterDeserialize_JSB = ForwardPipeline.prototype.init;

  class ForwardFlow extends nr.ForwardFlow {
    constructor() {
      super();
      this._name = 0;
      this._priority = 0;
      this._tag = 0;
      this._stages = [];
    }

    init() {
      for (let i = 0; i < this._stages.length; i++) {
        this._stages[i].init();
      }

      let info = new nr.RenderFlowInfo(this._name, this._priority, this._tag, this._stages);
      this.initialize(info);
    }

  }

  class ShadowFlow extends nr.ShadowFlow {
    constructor() {
      super();
      this._name = 0;
      this._priority = 0;
      this._tag = 0;
      this._stages = [];
    }

    init() {
      for (let i = 0; i < this._stages.length; i++) {
        this._stages[i].init();
      }

      let info = new nr.RenderFlowInfo(this._name, this._priority, this._tag, this._stages);
      this.initialize(info);
    }

  }

  class ForwardStage extends nr.ForwardStage {
    constructor() {
      super();
      this._name = 0;
      this._priority = 0;
      this._tag = 0;
      this.renderQueues = [];
    }

    init() {
      const queues = [];

      for (let i = 0; i < this.renderQueues.length; i++) {
        queues.push(this.renderQueues[i].init());
      }

      let info = new nr.RenderStageInfo(this._name, this._priority, this._tag, queues);
      this.initialize(info);
    }

  }

  class ShadowStage extends nr.ShadowStage {
    constructor() {
      super();
      this._name = 0;
      this._priority = 0;
      this._tag = 0;
    }

    init() {
      let info = new nr.RenderStageInfo(this._name, this._priority, this._tag, []);
      this.initialize(info);
    }

  }

  let instancedBufferProto = nr.InstancedBuffer;
  let oldGetFunc = instancedBufferProto.get;

  instancedBufferProto.get = function (pass) {
    return oldGetFunc.call(this, pass.handle);
  };

  class RenderQueueDesc {
    constructor() {
      this.isTransparent = false;
      this.sortMode = 0;
      this.stages = [];
    }

    init() {
      let desc = new nr.RenderQueueDesc(this.isTransparent, this.sortMode, this.stages);
      return desc;
    }

  }

  cc.js.setClassName('ForwardPipeline', ForwardPipeline);
  cc.js.setClassName('ForwardFlow', ForwardFlow);
  cc.js.setClassName('ShadowFlow', ShadowFlow);
  cc.js.setClassName('ForwardStage', ForwardStage);
  cc.js.setClassName('ShadowStage', ShadowStage);
  cc.js.setClassName('RenderQueueDesc', RenderQueueDesc);
  let getOrCreatePipelineState = nr.PipelineStateManager.getOrCreatePipelineState;

  nr.PipelineStateManager.getOrCreatePipelineState = function (device, pass, shader, renderPass, ia) {
    return getOrCreatePipelineState.call(this, pass.handle, shader, renderPass, ia);
  };

  const RootProto = cc.Root.prototype;
  Object.assign(RootProto, {
    createDefaultPipeline() {
      const pipeline = new nr.ForwardPipeline();
      const info = new nr.RenderPipelineInfo(0, []);
      pipeline.initialize(info);
      return pipeline;
    }

  });
})();

},{}],13:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
// JS to Native bridges
// set to lazy
Object.defineProperty(jsb, "reflection", {
  get: function () {
    if (jsb.__bridge !== undefined) return jsb.__bridge;

    if (window.JavascriptJavaBridge && cc.sys.os === cc.sys.OS_ANDROID) {
      jsb.__bridge = new JavascriptJavaBridge();
    } else if (window.JavaScriptObjCBridge && (cc.sys.os === cc.sys.OS_IOS || cc.sys.os === cc.sys.OS_OSX)) {
      jsb.__bridge = new JavaScriptObjCBridge();
    } else {
      jsb.__bridge = null;
    }

    return jsb.__bridge;
  },
  enumerable: true,
  configurable: true,
  set: function (value) {
    jsb.__bridge = value;
  }
});

},{}],14:[function(require,module,exports){
"use strict";

let SafeArea = cc.SafeArea;

if (SafeArea) {
  let _onEnable = SafeArea.prototype.onEnable;
  let _onDisable = SafeArea.prototype.onDisable;
  Object.assign(SafeArea.prototype, {
    onEnable() {
      _onEnable.call(this);

      this._adaptSafeAreaChangeWithThis = this.adaptSafeAreaChange.bind(this);
      this._updateAreaWithThis = this.adaptSafeAreaChange.bind(this);
      window.addEventListener('orientationchange', this._adaptSafeAreaChangeWithThis);
      window.addEventListener('safearea-change', this._updateAreaWithThis);
    },

    onDisable() {
      _onDisable.call(this);

      window.removeEventListener('orientationchange', this._adaptSafeAreaChangeWithThis);
      window.removeEventListener('safearea-change', this._updateAreaWithThis);
    },

    adaptSafeAreaChange() {
      if (JSB && (cc.sys.os === cc.sys.OS_IOS || cc.sys.os === cc.sys.OS_ANDROID)) {
        setTimeout(() => {
          this.updateArea();
        }, 200);
      }
    }

  });
}

},{}],15:[function(require,module,exports){
"use strict";

/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
const cacheManager = require('./jsb-cache-manager');

(function () {
  if (window.spine === undefined || window.middleware === undefined) return;
  middleware.generateGetSet(spine); // spine global time scale

  Object.defineProperty(spine, 'timeScale', {
    get() {
      return this._timeScale;
    },

    set(value) {
      this._timeScale = value;
      spine.SkeletonAnimation.setGlobalTimeScale(value);
    },

    configurable: true
  });

  let _slotColor = cc.color(0, 0, 255, 255);

  let _boneColor = cc.color(255, 0, 0, 255);

  let _meshColor = cc.color(255, 255, 0, 255);

  let _originColor = cc.color(0, 255, 0, 255);

  let skeletonDataProto = cc.internal.SpineSkeletonData.prototype;
  let _gTextureIdx = 1;
  let _textureKeyMap = {};

  let _textureMap = new WeakMap();

  let skeletonDataMgr = spine.SkeletonDataMgr.getInstance();
  spine.skeletonDataMgr = skeletonDataMgr;
  skeletonDataMgr.setDestroyCallback(function (textureIndex) {
    if (!textureIndex) return;
    let texKey = _textureKeyMap[textureIndex];

    if (texKey && _textureMap.has(texKey)) {
      _textureMap.delete(texKey);

      delete _textureKeyMap[textureIndex];
    }
  });
  let skeletonCacheMgr = spine.SkeletonCacheMgr.getInstance();
  spine.skeletonCacheMgr = skeletonCacheMgr;

  skeletonDataProto.destroy = function () {
    this.reset();
    skeletonCacheMgr.removeSkeletonCache(this._uuid);
    cc.Asset.prototype.destroy.call(this);
  };

  skeletonDataProto.reset = function () {
    if (this._skeletonCache) {
      spine.disposeSkeletonData(this._uuid);
      this._jsbTextures = null;
      this._skeletonCache = null;
    }

    this._atlasCache = null;
  };

  skeletonDataProto.getRuntimeData = function () {
    if (!this._skeletonCache) {
      this.init();
    }

    return this._skeletonCache;
  };

  skeletonDataProto.init = function () {
    if (this._skeletonCache) return;
    let uuid = this._uuid;

    if (!uuid) {
      cc.errorID(7504);
      return;
    }

    let skeletonCache = spine.retainSkeletonData(uuid);

    if (skeletonCache) {
      this._skeletonCache = skeletonCache;
      this.width = this._skeletonCache.getWidth();
      this.height = this._skeletonCache.getHeight();
      return;
    }

    let atlasText = this.atlasText;

    if (!atlasText) {
      cc.errorID(7508, this.name);
      return;
    }

    let textures = this.textures;
    let textureNames = this.textureNames;

    if (!(textures && textures.length > 0 && textureNames && textureNames.length > 0)) {
      cc.errorID(7507, this.name);
      return;
    }

    let jsbTextures = {};

    for (let i = 0; i < textures.length; ++i) {
      let texture = textures[i];
      let textureIdx = this.recordTexture(texture);
      let spTex = new middleware.Texture2D();
      spTex.setRealTextureIndex(textureIdx);
      spTex.setPixelsWide(texture.width);
      spTex.setPixelsHigh(texture.height);
      jsbTextures[textureNames[i]] = spTex;
    }

    this._jsbTextures = jsbTextures;
    let filePath = null;

    if (this.skeletonJsonStr) {
      filePath = this.skeletonJsonStr;
    } else {
      filePath = cacheManager.getCache(this.nativeUrl) || this.nativeUrl;
    }

    this._skeletonCache = spine.initSkeletonData(uuid, filePath, atlasText, jsbTextures, this.scale);

    if (this._skeletonCache) {
      this.width = this._skeletonCache.getWidth();
      this.height = this._skeletonCache.getHeight();
    }
  };

  skeletonDataProto.recordTexture = function (texture) {
    let index = _gTextureIdx;
    let texKey = _textureKeyMap[index] = {
      key: index
    };

    _textureMap.set(texKey, texture);

    _gTextureIdx++;
    return index;
  };

  skeletonDataProto.getTextureByIndex = function (textureIdx) {
    let texKey = _textureKeyMap[textureIdx];
    if (!texKey) return;
    return _textureMap.get(texKey);
  };

  let animation = spine.SkeletonAnimation.prototype; // The methods are added to be compatibility with old versions.

  animation.setCompleteListener = function (listener) {
    this._compeleteListener = listener;
    this.setCompleteListenerNative(function (trackEntry) {
      let loopCount = Math.floor(trackEntry.trackTime / trackEntry.animationEnd);
      this._compeleteListener && this._compeleteListener(trackEntry, loopCount);
    });
  }; // The methods are added to be compatibility with old versions.


  animation.setTrackCompleteListener = function (trackEntry, listener) {
    this._trackCompeleteListener = listener;
    this.setTrackCompleteListenerNative(trackEntry, function (trackEntryNative) {
      let loopCount = Math.floor(trackEntryNative.trackTime / trackEntryNative.animationEnd);
      this._trackCompeleteListener && this._trackCompeleteListener(trackEntryNative, loopCount);
    });
  }; // Temporary solution before upgrade the Spine API


  animation.setAnimationListener = function (target, callback) {
    this._target = target;
    this._callback = callback;
    let AnimationEventType = legacyCC.internal.SpineAnimationEventType;
    this.setStartListener(function (trackEntry) {
      if (this._target && this._callback) {
        this._callback.call(this._target, this, trackEntry, AnimationEventType.START, null, 0);
      }
    });
    this.setInterruptListener(function (trackEntry) {
      if (this._target && this._callback) {
        this._callback.call(this._target, this, trackEntry, AnimationEventType.INTERRUPT, null, 0);
      }
    });
    this.setEndListener(function (trackEntry) {
      if (this._target && this._callback) {
        this._callback.call(this._target, this, trackEntry, AnimationEventType.END, null, 0);
      }
    });
    this.setDisposeListener(function (trackEntry) {
      if (this._target && this._callback) {
        this._callback.call(this._target, this, trackEntry, AnimationEventType.DISPOSE, null, 0);
      }
    });
    this.setCompleteListener(function (trackEntry, loopCount) {
      if (this._target && this._callback) {
        this._callback.call(this._target, this, trackEntry, AnimationEventType.COMPLETE, null, loopCount);
      }
    });
    this.setEventListener(function (trackEntry, event) {
      if (this._target && this._callback) {
        this._callback.call(this._target, this, trackEntry, AnimationEventType.EVENT, event, 0);
      }
    });
  };

  let skeleton = cc.internal.SpineSkeleton.prototype;
  const AnimationCacheMode = cc.internal.SpineSkeleton.AnimationCacheMode;
  Object.defineProperty(skeleton, 'paused', {
    get() {
      return this._paused || false;
    },

    set(value) {
      this._paused = value;

      if (this._nativeSkeleton) {
        this._nativeSkeleton.paused(value);
      }
    }

  });
  Object.defineProperty(skeleton, "premultipliedAlpha", {
    get() {
      if (this._premultipliedAlpha === undefined) {
        return true;
      }

      return this._premultipliedAlpha;
    },

    set(value) {
      this._premultipliedAlpha = value;

      if (this._nativeSkeleton) {
        this._nativeSkeleton.setOpacityModifyRGB(this._premultipliedAlpha);
      }
    }

  });
  Object.defineProperty(skeleton, "timeScale", {
    get() {
      if (this._timeScale === undefined) return 1.0;
      return this._timeScale;
    },

    set(value) {
      this._timeScale = value;

      if (this._nativeSkeleton) {
        this._nativeSkeleton.setTimeScale(this._timeScale);
      }
    }

  });
  let _updateDebugDraw = skeleton._updateDebugDraw;

  skeleton._updateDebugDraw = function () {
    _updateDebugDraw.call(this);

    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setDebugMeshEnabled(this.debugMesh);

      this._nativeSkeleton.setDebugSlotsEnabled(this.debugSlots);

      this._nativeSkeleton.setDebugBonesEnabled(this.debugBones);
    }
  };

  let _updateUseTint = skeleton._updateUseTint;

  skeleton._updateUseTint = function () {
    _updateUseTint.call(this);

    if (this._nativeSkeleton) {
      this._nativeSkeleton.setUseTint(this.useTint);
    }
  };

  let _updateBatch = skeleton._updateBatch;

  skeleton._updateBatch = function () {
    _updateBatch.call(this);

    if (this._nativeSkeleton) {
      this._nativeSkeleton.setBatchEnabled(this.enableBatch);
    }
  };

  skeleton.setSkeletonData = function (skeletonData) {
    if (null != skeletonData.width && null != skeletonData.height) {
      const uiTrans = this.node._uiProps.uiTransformComp;
      uiTrans.setContentSize(skeletonData.width, skeletonData.height);
    }

    let uuid = skeletonData._uuid;

    if (!uuid) {
      cc.errorID(7504);
      return;
    }

    let texValues = skeletonData.textures;
    let texKeys = skeletonData.textureNames;

    if (!(texValues && texValues.length > 0 && texKeys && texKeys.length > 0)) {
      cc.errorID(7507, skeletonData.name);
      return;
    }

    if (this._nativeSkeleton) {
      this._nativeSkeleton.stopSchedule();

      this._nativeSkeleton._comp = null;
      this._nativeSkeleton = null;
    }

    let nativeSkeleton = null;

    if (this.isAnimationCached()) {
      nativeSkeleton = new spine.SkeletonCacheAnimation(uuid, this._cacheMode == AnimationCacheMode.SHARED_CACHE);
    } else {
      nativeSkeleton = new spine.SkeletonAnimation();

      try {
        spine.initSkeletonRenderer(nativeSkeleton, uuid);
      } catch (e) {
        cc._throw(e);

        return;
      }

      nativeSkeleton.setDebugSlotsEnabled(this.debugSlots);
      nativeSkeleton.setDebugMeshEnabled(this.debugMesh);
      nativeSkeleton.setDebugBonesEnabled(this.debugBones);
    }

    this._nativeSkeleton = nativeSkeleton;
    nativeSkeleton._comp = this;
    nativeSkeleton.setUseTint(this.useTint);
    nativeSkeleton.setOpacityModifyRGB(this.premultipliedAlpha);
    nativeSkeleton.setTimeScale(this.timeScale);
    nativeSkeleton.setBatchEnabled(this.enableBatch);
    let compColor = this.color;
    nativeSkeleton.setColor(compColor.r, compColor.g, compColor.b, compColor.a);
    this._skeleton = nativeSkeleton.getSkeleton(); // init skeleton listener

    this._startListener && this.setStartListener(this._startListener);
    this._endListener && this.setEndListener(this._endListener);
    this._completeListener && this.setCompleteListener(this._completeListener);
    this._eventListener && this.setEventListener(this._eventListener);
    this._interruptListener && this.setInterruptListener(this._interruptListener);
    this._disposeListener && this.setDisposeListener(this._disposeListener);
    this._sharedBufferOffset = nativeSkeleton.getSharedBufferOffset();
    this._sharedBufferOffset[0] = 0;
    this._useAttach = false;
    this._renderOrder = -1; // store render order and world matrix

    this._paramsBuffer = nativeSkeleton.getParamsBuffer();
    this.syncTransform(true);
    this.markForUpdateRenderData();
  };

  skeleton._updateColor = function () {
    if (this._nativeSkeleton) {
      let compColor = this.color;

      this._nativeSkeleton.setColor(compColor.r, compColor.g, compColor.b, compColor.a);
    }
  };

  skeleton.setAnimationStateData = function (stateData) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._stateData = stateData;
      return this._nativeSkeleton.setAnimationStateData(stateData);
    }
  };

  let _onEnable = skeleton.onEnable;

  skeleton.onEnable = function () {
    _onEnable.call(this);

    this._onSyncTransform();

    this.syncTransform(true);

    if (this._nativeSkeleton) {
      this._nativeSkeleton.onEnable();
    }

    middleware.retain();
  };

  let _onDisable = skeleton.onDisable;

  skeleton.onDisable = function () {
    _onDisable.call(this);

    this._offSyncTransform();

    if (this._nativeSkeleton) {
      this._nativeSkeleton.onDisable();
    }

    middleware.release();
  };

  skeleton.setVertexEffectDelegate = function (effectDelegate) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setVertexEffectDelegate(effectDelegate);
    }
  };

  skeleton.syncTransform = function (force) {
    let node = this.node;
    if (!node) return;
    let paramsBuffer = this._paramsBuffer;
    if (!paramsBuffer) return; // sync node world matrix to native

    node.updateWorldTransform();
    let worldMat = node._mat;
    paramsBuffer[1] = worldMat.m00;
    paramsBuffer[2] = worldMat.m01;
    paramsBuffer[3] = worldMat.m02;
    paramsBuffer[4] = worldMat.m03;
    paramsBuffer[5] = worldMat.m04;
    paramsBuffer[6] = worldMat.m05;
    paramsBuffer[7] = worldMat.m06;
    paramsBuffer[8] = worldMat.m07;
    paramsBuffer[9] = worldMat.m08;
    paramsBuffer[10] = worldMat.m09;
    paramsBuffer[11] = worldMat.m10;
    paramsBuffer[12] = worldMat.m11;
    paramsBuffer[13] = worldMat.m12;
    paramsBuffer[14] = worldMat.m13;
    paramsBuffer[15] = worldMat.m14;
    paramsBuffer[16] = worldMat.m15;
  };

  skeleton.update = function () {
    let nativeSkeleton = this._nativeSkeleton;
    if (!nativeSkeleton) return;
    let node = this.node;
    if (!node) return;
    let paramsBuffer = this._paramsBuffer;

    if (this._renderOrder != middleware.renderOrder) {
      paramsBuffer[0] = middleware.renderOrder;
      this._renderOrder = middleware.renderOrder;
      middleware.renderOrder++;
    }

    if (this.__preColor__ === undefined || !this.color.equals(this.__preColor__)) {
      let compColor = this.color;
      nativeSkeleton.setColor(compColor.r, compColor.g, compColor.b, compColor.a);
      this.__preColor__ = compColor;
    }

    const socketNodes = this.socketNodes;

    if (!this._useAttach && socketNodes.size > 0) {
      this._useAttach = true;
      nativeSkeleton.setAttachEnabled(true);
    }

    if (!this.isAnimationCached() && (this.debugBones || this.debugSlots || this.debugMesh) && this._debugRenderer) {
      let graphics = this._debugRenderer;
      graphics.clear();
      graphics.lineWidth = 5;
      let debugData = this._debugData || nativeSkeleton.getDebugData();
      if (!debugData) return;
      let debugIdx = 0,
          debugType = 0,
          debugLen = 0;

      while (true) {
        debugType = debugData[debugIdx++];
        if (debugType == 0) break;
        debugLen = debugData[debugIdx++];

        switch (debugType) {
          case 1:
            // slots
            graphics.strokeColor = _slotColor;

            for (let i = 0; i < debugLen; i += 8) {
              graphics.moveTo(debugData[debugIdx++], debugData[debugIdx++]);
              graphics.lineTo(debugData[debugIdx++], debugData[debugIdx++]);
              graphics.lineTo(debugData[debugIdx++], debugData[debugIdx++]);
              graphics.lineTo(debugData[debugIdx++], debugData[debugIdx++]);
              graphics.close();
              graphics.stroke();
            }

            break;

          case 2:
            // mesh
            graphics.strokeColor = _meshColor;

            for (let i = 0; i < debugLen; i += 6) {
              graphics.moveTo(debugData[debugIdx++], debugData[debugIdx++]);
              graphics.lineTo(debugData[debugIdx++], debugData[debugIdx++]);
              graphics.lineTo(debugData[debugIdx++], debugData[debugIdx++]);
              graphics.close();
              graphics.stroke();
            }

            break;

          case 3:
            // bones
            graphics.strokeColor = _boneColor;
            graphics.fillColor = _slotColor; // Root bone color is same as slot color.

            for (let i = 0; i < debugLen; i += 4) {
              let bx = debugData[debugIdx++];
              let by = debugData[debugIdx++];
              let x = debugData[debugIdx++];
              let y = debugData[debugIdx++]; // Bone lengths.

              graphics.moveTo(bx, by);
              graphics.lineTo(x, y);
              graphics.stroke(); // Bone origins.

              graphics.circle(bx, by, Math.PI * 1.5);
              graphics.fill();

              if (i === 0) {
                graphics.fillColor = _originColor;
              }
            }

            break;

          default:
            return;
        }
      }
    }
  };

  skeleton.updateWorldTransform = function () {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.updateWorldTransform();
    }
  };

  skeleton.setToSetupPose = function () {
    if (this._nativeSkeleton) {
      this._nativeSkeleton.setToSetupPose();
    }
  };

  skeleton.setBonesToSetupPose = function () {
    if (this._nativeSkeleton) {
      this._nativeSkeleton.setBonesToSetupPose();
    }
  };

  skeleton.setSlotsToSetupPose = function () {
    if (this._nativeSkeleton) {
      this._nativeSkeleton.setSlotsToSetupPose();
    }
  };

  skeleton.setSlotsRange = function (startSlotIndex, endSlotIndex) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setSlotsRange(startSlotIndex, endSlotIndex);
    }
  };

  skeleton.updateAnimationCache = function (animName) {
    if (!this.isAnimationCached()) return;

    if (this._nativeSkeleton) {
      if (animName) {
        this._nativeSkeleton.updateAnimationCache(animName);
      } else {
        this._nativeSkeleton.updateAllAnimationCache();
      }
    }
  };

  skeleton.invalidAnimationCache = function () {
    if (!this.isAnimationCached()) return;

    if (this._nativeSkeleton) {
      this._nativeSkeleton.updateAllAnimationCache();
    }
  };

  skeleton.findBone = function (boneName) {
    if (this._nativeSkeleton) return this._nativeSkeleton.findBone(boneName);
    return null;
  };

  skeleton.findSlot = function (slotName) {
    if (this._nativeSkeleton) return this._nativeSkeleton.findSlot(slotName);
    return null;
  };

  skeleton.setSkin = function (skinName) {
    if (this._nativeSkeleton) return this._nativeSkeleton.setSkin(skinName);
    return null;
  };

  skeleton.getAttachment = function (slotName, attachmentName) {
    if (this._nativeSkeleton) return this._nativeSkeleton.getAttachment(slotName, attachmentName);
    return null;
  };

  skeleton.setAttachment = function (slotName, attachmentName) {
    this._nativeSkeleton && this._nativeSkeleton.setAttachment(slotName, attachmentName);
  };

  skeleton.getTextureAtlas = function (regionAttachment) {
    cc.warn("Spine Skeleton getTextureAtlas not support in native");
    return null;
  };

  skeleton.setMix = function (fromAnimation, toAnimation, duration) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setMix(fromAnimation, toAnimation, duration);
    }
  };

  skeleton.setAnimation = function (trackIndex, name, loop) {
    if (this._nativeSkeleton) {
      if (this.isAnimationCached()) {
        return this._nativeSkeleton.setAnimation(name, loop);
      } else {
        return this._nativeSkeleton.setAnimation(trackIndex, name, loop);
      }
    }

    return null;
  };

  skeleton.addAnimation = function (trackIndex, name, loop, delay) {
    if (this._nativeSkeleton) {
      delay = delay || 0;

      if (this.isAnimationCached()) {
        return this._nativeSkeleton.addAnimation(name, loop, delay);
      } else {
        return this._nativeSkeleton.addAnimation(trackIndex, name, loop, delay);
      }
    }

    return null;
  };

  skeleton.findAnimation = function (name) {
    if (this._nativeSkeleton) return this._nativeSkeleton.findAnimation(name);
    return null;
  };

  skeleton.getCurrent = function (trackIndex) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      return this._nativeSkeleton.getCurrent(trackIndex);
    }

    return null;
  };

  skeleton.clearTracks = function () {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.clearTracks();
    }
  };

  skeleton.clearTrack = function (trackIndex) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.clearTrack(trackIndex);
    }
  };

  skeleton.setStartListener = function (listener) {
    this._startListener = listener;

    if (this._nativeSkeleton) {
      if (this.isAnimationCached()) {
        this._nativeSkeleton.setStartListener(function (animationName) {
          let self = this._comp;
          self._startEntry.animation.name = animationName;
          self._startListener && self._startListener(self._startEntry);
        });
      } else {
        this._nativeSkeleton.setStartListener(listener);
      }
    }
  };

  skeleton.setInterruptListener = function (listener) {
    this._interruptListener = listener;

    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setInterruptListener(listener);
    }
  };

  skeleton.setEndListener = function (listener) {
    this._endListener = listener;

    if (this._nativeSkeleton) {
      if (this.isAnimationCached()) {
        this._nativeSkeleton.setEndListener(function (animationName) {
          let self = this._comp;
          self._endEntry.animation.name = animationName;
          self._endListener && self._endListener(self._endEntry);
        });
      } else {
        this._nativeSkeleton.setEndListener(listener);
      }
    }
  };

  skeleton.setDisposeListener = function (listener) {
    this._disposeListener = listener;

    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setDisposeListener(listener);
    }
  };

  skeleton.setCompleteListener = function (listener) {
    this._completeListener = listener;

    if (this._nativeSkeleton) {
      if (this.isAnimationCached()) {
        this._nativeSkeleton.setCompleteListener(function (animationName) {
          let self = this._comp;
          self._endEntry.animation.name = animationName;
          self._completeListener && self._completeListener(self._endEntry);
        });
      } else {
        this._nativeSkeleton.setCompleteListener(listener);
      }
    }
  };

  skeleton.setEventListener = function (listener) {
    this._eventListener = listener;

    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setEventListener(listener);
    }
  };

  skeleton.setTrackStartListener = function (entry, listener) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setTrackStartListener(entry, listener);
    }
  };

  skeleton.setTrackInterruptListener = function (entry, listener) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setTrackInterruptListener(entry, listener);
    }
  };

  skeleton.setTrackEndListener = function (entry, listener) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setTrackEndListener(entry, listener);
    }
  };

  skeleton.setTrackDisposeListener = function (entry, listener) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setTrackDisposeListener(entry, listener);
    }
  };

  skeleton.setTrackCompleteListener = function (entry, listener) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setTrackCompleteListener(entry, listener);
    }
  };

  skeleton.setTrackEventListener = function (entry, listener) {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      this._nativeSkeleton.setTrackEventListener(entry, listener);
    }
  };

  skeleton.getState = function () {
    if (this._nativeSkeleton && !this.isAnimationCached()) {
      return this._nativeSkeleton.getState();
    }
  };

  skeleton._ensureListener = function () {
    cc.warn("Spine Skeleton _ensureListener not need in native");
  };

  skeleton._updateSkeletonData = function () {
    if (this.skeletonData) {
      this.skeletonData.init();
      this.setSkeletonData(this.skeletonData);
      this.attachUtil.init(this);
      this._preCacheMode = this._cacheMode;
      this.defaultSkin && this._nativeSkeleton.setSkin(this.defaultSkin);
      this.animation = this.defaultAnimation;
    } else {
      if (this._nativeSkeleton) {
        this._nativeSkeleton.stopSchedule();

        this._nativeSkeleton._comp = null;
        this._nativeSkeleton = null;
      }
    }
  };

  let _onDestroy = skeleton.onDestroy;

  skeleton.onDestroy = function () {
    _onDestroy.call(this);

    if (this._nativeSkeleton) {
      this._nativeSkeleton.stopSchedule();

      this._nativeSkeleton._comp = null;
      this._nativeSkeleton = null;
    }

    this._stateData = null;
  };

  let _tempAttachMat4 = new cc.mat4();

  let _tempVfmt, _tempBufferIndex, _tempIndicesOffset, _tempIndicesCount;

  skeleton._render = function (ui) {
    let nativeSkeleton = this._nativeSkeleton;
    if (!nativeSkeleton) return;
    let node = this.node;
    if (!node) return;
    let sharedBufferOffset = this._sharedBufferOffset;
    if (!sharedBufferOffset) return;
    let renderInfoOffset = sharedBufferOffset[0]; // reset render info offset

    sharedBufferOffset[0] = 0;
    const socketNodes = this.socketNodes;

    if (socketNodes.size > 0) {
      let attachInfoMgr = middleware.attachInfoMgr;
      let attachInfo = attachInfoMgr.attachInfo;
      let attachInfoOffset = sharedBufferOffset[1]; // reset attach info offset

      sharedBufferOffset[1] = 0;

      for (const boneIdx of socketNodes.keys()) {
        const boneNode = socketNodes.get(boneIdx); // Node has been destroy

        if (!boneNode || !boneNode.isValid) {
          socketNodes.delete(boneIdx);
          continue;
        }

        let tm = _tempAttachMat4;
        let matOffset = attachInfoOffset + boneIdx * 16;
        tm.m00 = attachInfo[matOffset];
        tm.m01 = attachInfo[matOffset + 1];
        tm.m04 = attachInfo[matOffset + 4];
        tm.m05 = attachInfo[matOffset + 5];
        tm.m12 = attachInfo[matOffset + 12];
        tm.m13 = attachInfo[matOffset + 13];
        boneNode.matrix = tm;
        boneNode.scale = this.node.scale;
      }
    }

    let renderInfoMgr = middleware.renderInfoMgr;
    let renderInfo = renderInfoMgr.renderInfo;
    let materialIdx = 0,
        realTextureIndex,
        realTexture; // verify render border

    let border = renderInfo[renderInfoOffset + materialIdx++];
    if (border !== 0xffffffff) return;
    let matLen = renderInfo[renderInfoOffset + materialIdx++];
    let useTint = this.useTint || this.isAnimationCached();
    let vfmt = useTint ? middleware.vfmtPosUvTwoColor : middleware.vfmtPosUvColor;
    _tempVfmt = vfmt;
    if (matLen == 0) return;

    for (let index = 0; index < matLen; index++) {
      realTextureIndex = renderInfo[renderInfoOffset + materialIdx++];
      realTexture = this.skeletonData.getTextureByIndex(realTextureIndex);
      if (!realTexture) return; // SpineMaterialType.TWO_COLORED 2
      // SpineMaterialType.COLORED_TEXTURED 0
      // cache material

      this.material = this.getMaterialForBlendAndTint(renderInfo[renderInfoOffset + materialIdx++], renderInfo[renderInfoOffset + materialIdx++], useTint ? 2 : 0);
      _tempBufferIndex = renderInfo[renderInfoOffset + materialIdx++];
      _tempIndicesOffset = renderInfo[renderInfoOffset + materialIdx++];
      _tempIndicesCount = renderInfo[renderInfoOffset + materialIdx++];

      if (middleware.indicesStart != _tempIndicesOffset || middleware.preRenderBufferIndex != _tempBufferIndex || middleware.preRenderBufferType != _tempVfmt) {
        ui.autoMergeBatches(middleware.preRenderComponent);
        middleware.resetIndicesStart = true;
      } else {
        middleware.resetIndicesStart = false;
      }

      ui.commitComp(this, realTexture._texture, this._assembler, null);
    }
  }; //////////////////////////////////////////
  // assembler


  const assembler = cc.internal.SpineAssembler;

  assembler.updateRenderData = function () {};

  assembler.fillBuffers = function (comp, renderer) {
    let nativeSkeleton = comp._skeleton;
    if (!nativeSkeleton) return;
    let node = comp.node;
    if (!node) return;
    let renderInfoLookup = middleware.RenderInfoLookup;
    let buffer = renderInfoLookup[_tempVfmt][_tempBufferIndex];
    renderer.currBufferBatch = buffer;

    if (middleware.resetIndicesStart) {
      buffer.indicesStart = _tempIndicesOffset;
    }

    buffer.indicesOffset = _tempIndicesOffset + _tempIndicesCount;
    middleware.indicesStart = buffer.indicesOffset;
    middleware.preRenderComponent = comp;
    middleware.preRenderBufferIndex = _tempBufferIndex;
    middleware.preRenderBufferType = _tempVfmt;
  };
})();

},{"./jsb-cache-manager":4}],16:[function(require,module,exports){
/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2020 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and  non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
'use strict';

const sys = cc.sys;
Object.assign(sys, {
  __init() {
    let platform = __getPlatform();

    this.isNative = true;
    this.isBrowser = false;
    this.platform = platform;
    this.isMobile = platform === this.ANDROID || platform === this.IPAD || platform === this.IPHONE || platform === this.WP8 || platform === this.TIZEN || platform === this.BLACKBERRY || platform === this.XIAOMI_QUICK_GAME || platform === this.VIVO_MINI_GAME || platform === this.OPPO_MINI_GAME || platform === this.HUAWEI_QUICK_GAME || platform === this.COCOSPLAY;
    this.os = __getOS();
    this.language = __getCurrentLanguage();

    const languageCode = __getCurrentLanguageCode();

    this.languageCode = languageCode ? languageCode.toLowerCase() : 'unknown';
    this.osVersion = __getOSVersion();
    this.osMainVersion = parseInt(this.osVersion);
    this.browserType = null;
    this.browserVersion = '';
    const w = window.innerWidth;
    const h = window.innerHeight;
    const ratio = window.devicePixelRatio || 1;
    this.windowPixelResolution = {
      width: window.nativeWidth || ratio * w,
      height: window.nativeHeight || ratio * h
    };
    this.localStorage = window.localStorage;
    let capabilities;
    capabilities = this.capabilities = {
      canvas: false,
      opengl: true,
      webp: true,
      imageBitmap: false,
      touches: this.isMobile,
      mouse: !this.isMobile,
      keyboard: !this.isMobile || window.JavascriptJavaBridge && cc.sys.os === cc.sys.OS_ANDROID,
      accelerometer: this.isMobile
    };
    this.__audioSupport = {
      ONLY_ONE: false,
      WEB_AUDIO: false,
      DELAY_CREATE_CTX: false,
      format: ['.mp3']
    };
    this.__videoSupport = {
      format: ['.mp4']
    };
  },

  getNetworkType: jsb.Device.getNetworkType,
  getBatteryLevel: jsb.Device.getBatteryLevel,
  garbageCollect: jsb.garbageCollect,
  restartVM: __restartVM,
  isObjectValid: __isObjectValid,

  openURL(url) {
    jsb.openURL(url);
  },

  getSafeAreaRect() {
    // x(top), y(left), z(bottom), w(right)
    var edge = jsb.Device.getSafeAreaEdge();
    var screenSize = cc.view.getFrameSize(); // Get leftBottom and rightTop point in UI coordinates

    var leftBottom = new cc.Vec2(edge.y, screenSize.height - edge.z);
    var rightTop = new cc.Vec2(screenSize.width - edge.w, edge.x); // Returns the real location in view.

    var relatedPos = {
      left: 0,
      top: 0,
      width: screenSize.width,
      height: screenSize.height
    };
    cc.view.convertToLocationInView(leftBottom.x, leftBottom.y, relatedPos, leftBottom);
    cc.view.convertToLocationInView(rightTop.x, rightTop.y, relatedPos, rightTop); // convert view point to design resolution size

    cc.view._convertPointWithScale(leftBottom);

    cc.view._convertPointWithScale(rightTop);

    return cc.rect(leftBottom.x, leftBottom.y, rightTop.x - leftBottom.x, rightTop.y - leftBottom.y);
  }

});

},{}],17:[function(require,module,exports){
/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
  worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
  not use Cocos Creator software for developing other software or tools that's
  used for developing games. You are not granted to publish, distribute,
  sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
'use strict';

if (cc.internal.VideoPlayer) {
  const {
    EventType
  } = cc.internal.VideoPlayer;
  let vec3 = cc.Vec3;
  let mat4 = cc.Mat4;

  let _mat4_temp = new mat4();

  let _topLeft = new vec3();

  let _bottomRight = new vec3();

  cc.internal.VideoPlayerImplManager.getImpl = function (componenet) {
    return new VideoPlayerImplJSB(componenet);
  };

  class VideoPlayerImplJSB extends cc.internal.VideoPlayerImpl {
    constructor(componenet) {
      super(componenet);
      this._matViewProj_temp = new mat4();
    }

    syncClip(clip) {
      this.removeVideoPlayer();

      if (!clip) {
        return;
      }

      this.createVideoPlayer(clip._nativeAsset);
    }

    syncURL(url) {
      this.removeVideoPlayer();

      if (!url) {
        return;
      }

      this.createVideoPlayer(url);
    }

    onCanplay() {
      if (this._loaded) {
        return;
      }

      this._loaded = true;
      this.video.setVisible(this._visible);
      this.dispatchEvent(EventType.READY_TO_PLAY);
      this.delayedPlay();
    }

    _bindEvent() {
      this.video.addEventListener('loadedmetadata', this.onLoadedMetadata.bind(this));
      this.video.addEventListener('suspend', this.onCanPlay.bind(this));
      this.video.addEventListener('play', this.onPlay.bind(this));
      this.video.addEventListener('pause', this.onPause.bind(this));
      this.video.addEventListener('stoped', this.onStoped.bind(this));
      this.video.addEventListener('click', this.onClick.bind(this));
      this.video.addEventListener('ended', this.onEnded.bind(this));
    }

    onLoadedMetadata() {
      this._loadedMeta = true;
      this._forceUpdate = true;

      if (this._visible) {
        this.enable();
      } else {
        this.disable();
      }

      this.dispatchEvent(EventType.META_LOADED);
      this.delayedFullScreen();
      this.delayedPlay();
    }

    createVideoPlayer(url) {
      this._video = new jsb.VideoPlayer();

      this._bindEvent();

      this._video.setVisible(this._visible);

      this._video.setURL(url);

      this._forceUpdate = true;
    }

    removeVideoPlayer() {
      let video = this.video;

      if (video) {
        video.stop();
        video.setVisible(false);
        video.destroy();
        this._playing = false;
        this._loaded = false;
        this._loadedMeta = false;
        this._ignorePause = false;
        this._cachedCurrentTime = 0;
        this._video = null;
      }
    }

    getDuration() {
      if (!this.video) {
        return -1;
      }

      return this.video.duration();
    }

    syncPlaybackRate() {
      cc.warn('The platform does not support');
    }

    syncVolume() {
      cc.warn('The platform does not support');
    }

    syncMute() {
      cc.warn('The platform does not support');
    }

    syncLoop() {
      cc.warn('The platform does not support');
    }

    syncStayOnBottom() {
      cc.warn('The platform does not support');
    }

    getCurrentTime() {
      if (this.video) {
        return this.video.currentTime();
      }

      return -1;
    }

    seekTo(val) {
      let video = this._video;
      if (!video) return;
      video.seekTo(val);
    }

    disable(noPause) {
      if (this.video) {
        if (!noPause) {
          this.video.pause();
        }

        this.video.setVisible(false);
        this._visible = false;
      }
    }

    enable() {
      if (this.video) {
        this.video.setVisible(true);
        this._visible = true;
      }
    }

    canPlay() {
      this.video.play();
      this.syncCurrentTime();
    }

    resume() {
      if (this.video) {
        this.video.resume();
        this.syncCurrentTime();
        this._playing = true;
      }
    }

    pause() {
      if (this.video) {
        this._cachedCurrentTime = this.video.currentTime();
        this.video.pause();
      }
    }

    stop() {
      if (this.video) {
        this._ignorePause = true;
        this.video.seekTo(0);
        this._cachedCurrentTime = 0;
        this.video.stop();
      }
    }

    canFullScreen(enabled) {
      if (this.video) {
        this.video.setFullScreenEnabled(enabled);
      }
    }

    syncKeepAspectRatio(enabled) {
      if (this.video) {
        this.video.setKeepAspectRatioEnabled(enabled);
      }
    }

    syncMatrix() {
      if (!this._video || !this._component || !this._uiTrans) return;
      const camera = this.UICamera;

      if (!camera) {
        return;
      }

      this._component.node.getWorldMatrix(_mat4_temp);

      const {
        width,
        height
      } = this._uiTrans.contentSize;

      if (!this._forceUpdate && camera.matViewProj.equals(this._matViewProj_temp) && this._m00 === _mat4_temp.m00 && this._m01 === _mat4_temp.m01 && this._m04 === _mat4_temp.m04 && this._m05 === _mat4_temp.m05 && this._m12 === _mat4_temp.m12 && this._m13 === _mat4_temp.m13 && this._w === width && this._h === height) {
        return;
      }

      this._matViewProj_temp.set(camera.matViewProj); // update matrix cache


      this._m00 = _mat4_temp.m00;
      this._m01 = _mat4_temp.m01;
      this._m04 = _mat4_temp.m04;
      this._m05 = _mat4_temp.m05;
      this._m12 = _mat4_temp.m12;
      this._m13 = _mat4_temp.m13;
      this._w = width;
      this._h = height;
      let canvas_width = cc.game.canvas.width;
      let canvas_height = cc.game.canvas.height;
      let ap = this._uiTrans.anchorPoint; // Vectors in node space

      vec3.set(_topLeft, -ap.x * this._w, (1.0 - ap.y) * this._h, 0);
      vec3.set(_bottomRight, (1 - ap.x) * this._w, -ap.y * this._h, 0); // Convert to world space

      vec3.transformMat4(_topLeft, _topLeft, _mat4_temp);
      vec3.transformMat4(_bottomRight, _bottomRight, _mat4_temp); // need update camera data

      camera.update(); // Convert to Screen space

      camera.worldToScreen(_topLeft, _topLeft);
      camera.worldToScreen(_bottomRight, _bottomRight);
      let finalWidth = _bottomRight.x - _topLeft.x;
      let finalHeight = _topLeft.y - _bottomRight.y;

      this._video.setFrame(_topLeft.x, canvas_height - _topLeft.y, finalWidth, finalHeight);

      this._forceUpdate = false;
    }

  }
}

},{}],18:[function(require,module,exports){
/****************************************************************************
 Copyright (c) 2017-2020 Xiamen Yaji Software Co., Ltd.

 https://www.cocos.com/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
'use strict';

if (cc.internal.WebView) {
  const {
    EventType
  } = cc.internal.WebView;
  let vec3 = cc.Vec3;
  let mat4 = cc.Mat4;

  let _mat4_temp = new mat4();

  let _topLeft = new vec3();

  let _bottomRight = new vec3();

  cc.internal.WebViewImplManager.getImpl = function (componenet) {
    return new WebViewImplJSB(componenet);
  };

  class WebViewImplJSB extends cc.internal.WebViewImpl {
    constructor(componenet) {
      super(componenet);
      this.jsCallback = null;
      this.interfaceSchema = null;
      this._matViewProj_temp = new mat4();
    }

    _bindEvent() {
      let onLoaded = () => {
        this._forceUpdate = true;
        this.dispatchEvent(EventType.LOADED);
      };

      let onError = () => {
        this.dispatchEvent(EventType.ERROR);
      };

      this.webview.setOnDidFinishLoading(onLoaded);
      this.webview.setOnDidFailLoading(onError);
      this.jsCallback && this.setOnJSCallback(this.jsCallback);
      this.interfaceSchema && this.setJavascriptInterfaceScheme(this.interfaceSchema); // remove obj

      this.jsCallback = null;
      this.interfaceSchema = null;
    }

    createWebView() {
      if (!jsb.WebView) {
        console.warn('jsb.WebView is null');
        return;
      }

      this._webview = jsb.WebView.create();

      this._bindEvent();
    }

    removeWebView() {
      let webview = this.webview;

      if (webview) {
        this.webview.destroy();
        this.reset();
      }
    }

    disable() {
      if (this.webview) {
        this.webview.setVisible(false);
      }
    }

    enable() {
      if (this.webview) {
        this.webview.setVisible(true);
      }
    }

    setOnJSCallback(callback) {
      let webview = this.webview;

      if (webview) {
        webview.setOnJSCallback(callback);
      } else {
        this.jsCallback = callback;
      }
    }

    setJavascriptInterfaceScheme(scheme) {
      let webview = this.webview;

      if (webview) {
        webview.setJavascriptInterfaceScheme(scheme);
      } else {
        this.interfaceSchema = scheme;
      }
    }

    loadURL(url) {
      let webview = this.webview;

      if (webview) {
        webview.src = url;
        webview.loadURL(url);
        this.dispatchEvent(EventType.LOADING);
      }
    }

    evaluateJS(str) {
      let webview = this.webview;

      if (webview) {
        return webview.evaluateJS(str);
      }
    }

    syncMatrix() {
      if (!this._webview || !this._component || !this._uiTrans) return;
      const camera = this.UICamera;

      if (!camera) {
        return;
      }

      this._component.node.getWorldMatrix(_mat4_temp);

      const {
        width,
        height
      } = this._uiTrans.contentSize;

      if (!this._forceUpdate && camera.matViewProj.equals(this._matViewProj_temp) && this._m00 === _mat4_temp.m00 && this._m01 === _mat4_temp.m01 && this._m04 === _mat4_temp.m04 && this._m05 === _mat4_temp.m05 && this._m12 === _mat4_temp.m12 && this._m13 === _mat4_temp.m13 && this._w === width && this._h === height) {
        return;
      }

      this._matViewProj_temp.set(camera.matViewProj); // update matrix cache


      this._m00 = _mat4_temp.m00;
      this._m01 = _mat4_temp.m01;
      this._m04 = _mat4_temp.m04;
      this._m05 = _mat4_temp.m05;
      this._m12 = _mat4_temp.m12;
      this._m13 = _mat4_temp.m13;
      this._w = width;
      this._h = height;
      let canvas_width = cc.game.canvas.width;
      let canvas_height = cc.game.canvas.height;
      let ap = this._uiTrans.anchorPoint; // Vectors in node space

      vec3.set(_topLeft, -ap.x * this._w, (1.0 - ap.y) * this._h, 0);
      vec3.set(_bottomRight, (1 - ap.x) * this._w, -ap.y * this._h, 0); // Convert to world space

      vec3.transformMat4(_topLeft, _topLeft, _mat4_temp);
      vec3.transformMat4(_bottomRight, _bottomRight, _mat4_temp); // need update camera data

      camera.update(); // Convert to Screen space

      camera.worldToScreen(_topLeft, _topLeft);
      camera.worldToScreen(_bottomRight, _bottomRight);
      let finalWidth = _bottomRight.x - _topLeft.x;
      let finalHeight = _topLeft.y - _bottomRight.y;

      this._webview.setFrame(_topLeft.x, canvas_height - _topLeft.y, finalWidth, finalHeight);

      this._forceUpdate = false;
    }

  }
}

},{}]},{},[1]);
