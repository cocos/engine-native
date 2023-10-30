require('./src/settings.js');
require('./jsb-adapter/jsb-builtin.js');
require('./src/cocos2d-jsb.js');
require('./src/physics.js');
require('./jsb-adapter/jsb-engine.js');

<%commonJSModuleMap%>

globalThis.oh.loadModule = (name) => {
    commonJSModuleMap[name]?.();
};
globalThis.oh.loadJsList = (jsList, cb) => {
    globalThis.cc.assetManager.loadScript(jsList.map(function (x) { return x; }), cb);
};