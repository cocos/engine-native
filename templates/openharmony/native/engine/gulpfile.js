const gulp = require('gulp');
const Del = require('del');
const through = require('through2');
const minimist = require('minimist');

var options = {
    default: {
        path: 'jsb-link',
    }
};

var options = minimist(process.argv.slice(2), options);
const tempPath = options.path;

try {
    const fs = require('fs');
    const convert = require('xml-js');
    let xmlPath = `./${tempPath}/frameworks/runtime-src/proj.android-studio/instantapp/AndroidManifest.xml`;
    let json5path = './openharmony/entry/src/main/module.json5'

    let xml = fs.readFileSync(xmlPath, 'utf-8');
    let xmlResult = JSON.parse(convert.xml2json(xml, { compact: true, spaces: 4 }));

    let json = fs.readFileSync(json5path, 'utf-8');
    let jsonResult = JSON.parse(json);
    let orientation = xmlResult.manifest.application.activity._attributes['android:screenOrientation'];
    let jsonOrientation = jsonResult.module.abilities[0].orientation;
    switch (orientation) {
        case 'unspecified':// 默认值，由系统决定，不同手机可能不一致
            jsonOrientation = "unspecified";
            break;
        case 'fullSensor':// 显示的方向（4个方向）是由设备的方向传感器来决定的
            jsonOrientation = "auto_rotation";
            break;
        case 'portrait':// 强制竖屏显示
            jsonOrientation = "portrait";
            break;
        case 'landscape':// 强制横屏显示
            jsonOrientation = "landscape";
            break;
        case 'reversePortrait':// 竖屏倒转
            jsonOrientation = "portrait_inverted";
            break;
        case 'reverseLandscape':// 横屏倒转
            jsonOrientation = "landscape_inverted";
            break;
        case 'sensorLandscape'://  横向显示，但是基于设备传感器
            jsonOrientation = "auto_rotation_landscape";
            break;
        case 'sensorPortrait'://  竖向显示，但是基于设备传感器
            jsonOrientation = "auto_rotation_portrait";
            break;
        default:
            break;
    }
    jsonResult.module.abilities[0].orientation = jsonOrientation;
    fs.writeFileSync(json5path, JSON.stringify(jsonResult, null, '\t'));
} catch (error) {
    console.log("修改屏幕朝向出错，请手动修改，路径：./openharmony/entry/src/main/module.json5")
}


/**
 * clean
 */

// 清理lib-src
gulp.task('clean-src', function () {
    return Del(['./openharmony/entry/lib/src/']);
});

// 清理resources-assets
gulp.task('clean-assets', function () {
    return Del(['./openharmony/entry/src/main/resources/rawfile/assets/']);
});

// 清理lib-assets-index
gulp.task('clean-index', function () {
    return Del(['./openharmony/entry/lib/assets/']);
});

// 清理lib-jsb
gulp.task('clean-jsb', async function (done) {
    return await Del(['./openharmony/entry/lib/jsb-adapter/']);
});

/**
 * copy
 */
// 拷贝assets-index.js待改进
gulp.task('copy-index', function () {
    return gulp.src(`./${tempPath}/assets/**/index*`)
        .pipe(gulp.dest('./openharmony/entry/lib/assets'));
});

// 拷贝remote-index.js
gulp.task('copy-remote-index', function () {
    return gulp.src(`./${tempPath}/remote/**/index*`)
        .pipe(gulp.dest('./openharmony/entry/lib/assets'));
});

// 拷贝resources-assets
gulp.task('copy-assets', function () {
    return gulp.src([`./${tempPath}/assets/**/*`, `!./${tempPath}/assets/**/*.js`])
        .pipe(gulp.dest('./openharmony/entry/src/main/resources/rawfile/assets'));
});

// 拷贝lib-jsb
gulp.task('copy-jsb', function () {
    return gulp.src(['./code/**', '!./code/cocos2d-jsb*'])
        .pipe(gulp.dest(['./openharmony/entry/lib/jsb-adapter/']));
});

// 拷贝lib-jsb
gulp.task('copy-cocos2d', function () {
    return gulp.src(['./code/cocos2d-jsb*'])
        .pipe(gulp.dest(['./openharmony/entry/lib/src']));
});

// 拷贝lib-src
gulp.task('copy-src', function () {
    return gulp.src([`./${tempPath}/src/**/*`, `!./${tempPath}/src/cocos2d-jsb*`])
        .pipe(gulp.dest('./openharmony/entry/lib/src'));
});

/**
 * revise
 */
let indexPaths = [];
// 获取路径并保存
gulp.task('getIndexPaths', function () {
    return gulp.src('./openharmony/entry/lib/assets/**/*.js')
        .pipe(through.obj(function (file, enc, callback) {
            this.push(file.path);
            callback();
        })).on('data', function (data) {
            indexPaths.push(data);
        })
});

// 转换路径
gulp.task('transformIndexPath', (done) => {
    for (let i = 0; i < indexPaths.length; i++) {
        let temp = indexPaths[i].split("\\");
        const pass = temp.length - 3;
        temp = temp.filter((v, i) => { return i >= pass });
        indexPaths[i] = temp.join("/");
    }
    done();
});

// 获取路径并转换
gulp.task('indexPath', gulp.series('getIndexPaths', 'transformIndexPath'));

// 拷贝lib-src
let jsPath = [];
let settings = '';
let physics = '';
gulp.task('getJsPaths', function () {
    return gulp.src('./openharmony/entry/lib/src/assets/**/*.js')
        .pipe(through.obj(function (file, enc, callback) {
            this.push(file.path);
            callback();
        })).on('data', function (data) {
            jsPath.push(data);
        })
});

gulp.task('getSpPaths', function () {
    return gulp.src(['./openharmony/entry/lib/src/**/*.js', '!./openharmony/entry/lib/src/assets/'])
        .pipe(through.obj(function (file, enc, callback) {
            if (file.path.includes('physics')) {
                physics = file.path.split('\\').pop();
            }
            if (file.path.includes('settings')) {
                settings = file.path.split('\\').pop();
            }
            callback();
        }))
});


// 转换路径
gulp.task('transformJsPath', (done) => {
    for (let i = 0; i < jsPath.length; i++) {
        let temp = jsPath[i].split("\\");
        const pass = temp.lastIndexOf('assets');
        temp = temp.filter((v, i) => { return i >= pass });
        jsPath[i] = temp.join("/");
    }
    done();
});

// 获取lib-src-js 并修改 index.js
gulp.task('revise-src-index', async (done) => {
    return gulp.src("./openharmony/entry/lib/index.js")
        .pipe(through.obj(function (file, enc, callback) {
            var result = 'require(\'./src/' + settings + '\');\n';
            result += 'require(\'./jsb-adapter/jsb-builtin.js\');\nrequire(\'./src/cocos2d-jsb.js\');\n'
            if (physics != '') {
                result += 'require(\'./src/' + physics + '\');\n';
            }
            result += 'require(\'./jsb-adapter/jsb-engine.js\');\n';
            result += '\nconst commonJSModuleMap = {\n'
            for (let i = 0; i < indexPaths.length; i++) {
                const e = indexPaths[i];
                result = result.concat('\t\'' + e + '\': () => { require(\'./' + e + '\') },\n');
            }
            for (let i = 0; i < jsPath.length; i++) {
                const e = jsPath[i];
                result = result.concat('\t\'' + e + '\': () => { require(\'./src/' + e + '\') },\n');
            }
            result += '}\nglobalThis.oh.loadModule = (name) => {\n\tcommonJSModuleMap[name]?.();\n};\n'
            result += 'globalThis.oh.loadJsList = (jsList, cb) => {\n\tglobalThis.cc.assetManager.loadScript(jsList.map(function (x) { return x; }), cb);\n};';
            file.contents = new Buffer.from(result);
            this.push(file);
            callback();
        }))
        .pipe(gulp.dest('./openharmony/entry/lib/', { overwrite: true }));
});

// 获取路径并转换
gulp.task('jsPath', gulp.series('getJsPaths', 'getSpPaths', 'transformJsPath', 'revise-src-index'));

// 获取包名 版本
let projectInfo = {};
gulp.task('getPack', function () {
    return gulp.src(`./${tempPath}/.cocos-project*`)
        .pipe(through.obj(function (file, enc, callback) {
            let data = {
                packageName: JSON.parse(`${file.contents}`).packageName,
                name: JSON.parse(`${file.contents}`).projectName,
            }
            projectInfo = data;
            callback();
        }))
});

gulp.task('revise_name', function () {
    return gulp.src('./openharmony/AppScope/resources/base/element/string.json*')
        .pipe(through.obj(function (file, enc, callback) {
            let tempJson = JSON.parse(`${file.contents}`);
            tempJson.string[0].value = projectInfo.name;
            file.contents = new Buffer.from(JSON.stringify(tempJson));
            this.push(file);
            callback();
        }))
        .pipe(gulp.dest('./openharmony/AppScope/resources/base/element/', { overwrite: true }))
});

gulp.task('revise_packageName', function () {
    return gulp.src('./openharmony/AppScope/app.json*')
        .pipe(through.obj(function (file, enc, callback) {
            let tempJson = JSON.parse(`${file.contents}`);
            tempJson.app.bundleName = projectInfo.packageName;
            file.contents = new Buffer.from(JSON.stringify(tempJson));
            this.push(file);
            callback();
        }))
        .pipe(gulp.dest('./openharmony/AppScope/', { overwrite: true }))
});

gulp.task('packageInfo', gulp.series('getPack', 'revise_name', 'revise_packageName'));


// build
gulp.task('build', gulp.series(
    gulp.parallel('clean-assets', 'clean-index', 'clean-src', 'clean-jsb'),
    gulp.parallel('copy-assets', 'copy-index', 'copy-remote-index', 'copy-src', 'copy-jsb', 'copy-cocos2d')
));

// default task
gulp.task('default', gulp.series('build', 'indexPath', 'jsPath', 'packageInfo'));




