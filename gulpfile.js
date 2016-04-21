'use strict';

var gulp = require('gulp');
var gulpSequence = require('gulp-sequence');
var zip = require('gulp-zip');
var Ftp = require('ftp');
var ExecSync = require('child_process').execSync;
var spawn = require('child_process').spawn;
var Path = require('path');
var cocosConsoleRoot = './tools/cocos2d-console/bin';
var cocosConsoleBin;
if (process.platform === 'darwin') {
  cocosConsoleBin = Path.join(cocosConsoleRoot, 'cocos');
}
else {
  cocosConsoleBin = Path.join(cocosConsoleRoot, 'cocos.bat');
}

gulp.task('make-cocos2d-x', gulpSequence('gen-cocos2d-x', 'upload-cocos2d-x'));
gulp.task('make-platform', gulpSequence('make-prebuilt', 'make-simulator'));
gulp.task('make-prebuilt', gulpSequence('gen-libs', 'archive-prebuilt', 'upload-prebuilt'));
gulp.task('make-simulator', gulpSequence('gen-simulator', 'archive-simulator', 'upload-simulator'));

function execSync(cmd, workPath) {
  var execOptions = {
    cwd : workPath,
    stdio : 'inherit'
  };
  ExecSync(cmd, execOptions);
}

function upload2Ftp(localPath, ftpPath, config, cb) {
  var ftpClient = new Ftp();
  ftpClient.on('error', function(err) {
    if (err) {
      cb(err);
    }
  });
  ftpClient.on('ready', function() {
    var dirName = Path.dirname(ftpPath);
    ftpClient.mkdir(dirName, true, function(err) {
      if (err) {
        cb(err);
      }
    });

    ftpClient.put(localPath, ftpPath, function(err) {
      if (err) {
        cb(err);
      }
      ftpClient.end();
      cb();
    });
  });

  // connect to ftp
  ftpClient.connect(config);
}

function uploadZipFile (zipFileName, path, cb) {
  var remotePath = Path.join('TestBuilds','Fireball', 'cocos2d-x', zipFileName);
  var zipFilePath = Path.join(path, zipFileName);
  upload2Ftp(zipFilePath, remotePath, {
    host: '192.168.52.109',
    user: 'xmdev',
    password: 'chukongxm'
  },function(err) {
    if (err) {
      throw err;
    }
    cb();
  });
}

gulp.task('init', function(cb) {
  execSync('python download-deps.py', '.');
  execSync('git submodule update --init', '.');
  cb();
});

gulp.task('gen-libs', function(cb) {
  execSync( cocosConsoleBin + ' gen-libs -m release', './');
  cb();
});

gulp.task('gen-cocos2d-x', function (cb) {
  execSync('./git-archive-all cocos2d-x.zip', './tools/make-package');
  cb();
});

gulp.task('gen-simulator', function (cb) {
  var args;
  if (process.platform === 'darwin') {
    args = ['gen-simulator', '-m', 'debug', '-p', 'mac'];
  }
  else {
    args = ['gen-simulator', '-m', 'debug', '-p', 'win32', '--vs', '2013', '--ol', 'en'];
  }
  try {
    var child = spawn(cocosConsoleBin, args);
    child.stdout.on('data', function (data) {
      console.log(data.toString());
    });
    child.stderr.on('data', function (data) {
      console.error(data.toString());
    });
    child.on('close', (code) => {
      if (code !== 0) {
        console.error('Generate simulator failed');
        cb();
        return;
      }
    });
    child.on('error', function () {
      console.error('Generate simulator failed');
      cb();
    });
  }
  catch (err) {
    console.error(err);
    cb();
    return;
  }
});

gulp.task('archive-simulator', function () {
  return gulp.src('./simulator/**/*')
    .pipe(zip('simulator_' + process.platform + '.zip'))
    .pipe(gulp.dest('./'));
});

gulp.task('archive-prebuilt', function () {
  return gulp.src('./prebuilt/**/*', {
    base: './'
  }).pipe(zip('prebuilt_' + process.platform + '.zip'))
    .pipe(gulp.dest('./'));
});

gulp.task('upload-prebuilt', function (cb) {
  var zipFileName = 'prebuilt_' + process.platform + '.zip';
  uploadZipFile(zipFileName, '.', cb);
});

gulp.task('upload-cocos2d-x', function (cb) {
  var zipFileName = 'cocos2d-x.zip';
  uploadZipFile(zipFileName, './tools/make-package', cb);
});

gulp.task('upload-simulator', function (cb) {
  var zipFileName = 'simulator_' + process.platform + '.zip';
  uploadZipFile(zipFileName, '.', cb);
});