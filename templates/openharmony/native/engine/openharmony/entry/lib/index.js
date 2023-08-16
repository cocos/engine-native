require('./src/settings.js');
require('./jsb-adapter/jsb-builtin.js');
require('./src/cocos2d-jsb.js');
require('./src/physics.js');
require('./jsb-adapter/jsb-engine.js');

const commonJSModuleMap = {
	'assets/internal/index.js': () => { require('./assets/internal/index.js') },
	'assets/main/index.js': () => { require('./assets/main/index.js') },
	'assets/res1/index.js': () => { require('./assets/res1/index.js') },
	'assets/res2/index.js': () => { require('./assets/res2/index.js') },
	'assets/resources/index.js': () => { require('./assets/resources/index.js') },
}
globalThis.oh.loadModule = (name) => {
	commonJSModuleMap[name]?.();
};
globalThis.oh.loadJsList = (jsList, cb) => {
	globalThis.cc.assetManager.loadScript(jsList.map(function (x) { return x; }), cb);
};