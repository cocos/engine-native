#!/bin/bash
set -e
set -x

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..

if [ -z "$NDK_ROOT" ]; then
    export NDK_ROOT=$HOME/bin/android-ndk
fi

# to fix git error: shallow update not allowed
# https://stackoverflow.com/questions/28983842/remote-rejected-shallow-update-not-allowed-after-changing-git-remote-url
# git remote add old https://github.com/cocos-creator/cocos2d-x-lite
# git fetch --unshallow old

export GH_EMAIL=jiangzhan1988@gmail.com
export GH_USER=plutoo
export GH_PASSWORD=Fighterjiang123

cd $COCOS2DX_ROOT/tools/travis-scripts
./generate-bindings.sh $TRAVIS_BRANCH

cd $COCOS2DX_ROOT/tools/travis-scripts
./generate-cocosfiles.sh $TRAVIS_BRANCH
exit 0
