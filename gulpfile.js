'use strict';

var gulp = require('gulp');
var gulpSequence = require('gulp-sequence');
var zip = require('gulp-zip');
var Ftp = require('ftp');
var ExecSync = require('child_process').execSync;
var Path = require('path');

gulp.task('make-cocos2d-x', gulpSequence('gen-cocos2d-x', 'upload-cocos2d-x'));
gulp.task('make-prebuilt', gulpSequence('gen-libs', 'archive-prebuilt', 'upload-prebuilt'));

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
  execSync('./tools/cocos2d-console/bin/cocos gen-libs -m release', '.');
  cb();
});

gulp.task('gen-cocos2d-x', function (cb) {
  execSync('./git-archive-all cocos2d-x.zip', './tools/make-package');
  cb();
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