/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.
 Copyright (c) 2017-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "VideoPlayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_OPENHARMONY)
#include <cstdlib>
#include "base/std/container/string.h"
#include "platform/CCFileUtils.h"
#include "platform/openharmony/napi/NapiHelper.h"

NS_CC_BEGIN

#define QUIT_FULLSCREEN 1000

int createAvPalyer() {
    int32_t value = 0;
    NapiHelper::napiCallFunction("createAVPlayer", &value);
    return value;
}

VideoPlayer::VideoPlayer()
: _videoPlayerIndex(-1),
  _fullScreenEnabled(false),
  _fullScreenDirty(false),
  _keepAspectRatioEnabled(false) {
    _videoPlayerIndex = createAvPalyer();

    #if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
    #endif
}

VideoPlayer::~VideoPlayer() {
    if (_videoPlayerIndex != -1 ) {
        int32_t value = 0;
        NapiHelper::napiCallFunction("destroy", &value);
        _videoPlayerIndex = -1;
    }
}

void VideoPlayer::setURL(const ccstd::string &videoUrl) {
    if (videoUrl.find("://") == ccstd::string::npos) {
        _videoURL = FileUtils::getInstance()->fullPathForFilename(videoUrl);
        _videoSource = VideoPlayer::Source::FILENAME;
    } else {
        _videoURL = videoUrl;
        _videoSource = VideoPlayer::Source::URL;
    }
    int32_t value = 0;
    NapiHelper::napiCallFunctionByStrArgs("setURL", _videoURL, &value);
}

void VideoPlayer::VideoPlayer::setFrame(float x, float y, float width, float height) {
    // todo openharmony not support
}

void VideoPlayer::setFullScreenEnabled(bool fullscreen) {
    // todo openharmony not support
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable) {
    // todo openharmony not support
}

void VideoPlayer::play() {
    int32_t value = 0;
    NapiHelper::napiCallFunction("play", &value);
}

void VideoPlayer::pause() {
    int32_t value = 0;
    NapiHelper::napiCallFunction("pause", &value);
}

void VideoPlayer::stop() {
    int32_t value = 0;
    NapiHelper::napiCallFunction("stop", &value);
}

void VideoPlayer::seekTo(float sec) {
    int32_t value = 0;
    NapiHelper::napiCallFunctionByFloatArgs("seekTo", sec, &value);
}

void VideoPlayer::setVisible(bool visible) {
    // todo openharmony cannot support
}

void VideoPlayer::addEventListener(const ccstd::string &name, const VideoPlayer::ccVideoPlayerCallback &callback) {
    _eventCallback[name] = callback;
}

void VideoPlayer::onPlayEvent(int event) {
    if (event == QUIT_FULLSCREEN) {
        _fullScreenEnabled = false;
    } else {
        auto videoEvent = static_cast<VideoPlayer::EventType>(event);

        switch (videoEvent) {
            case EventType::PLAYING:
                _eventCallback["play"]();
                break;
            case EventType::PAUSED:
                _eventCallback["pause"]();
                break;
            case EventType::STOPPED:
                _eventCallback["stoped"]();
                break;
            case EventType::COMPLETED:
                _eventCallback["ended"]();
                break;
            case EventType::META_LOADED:
                _eventCallback["loadedmetadata"]();
                break;
            case EventType::CLICKED:
                _eventCallback["click"]();
                break;
            case EventType::READY_TO_PLAY:
                _eventCallback["suspend"]();
                break;
            default:
                break;
        }
    }
}

float VideoPlayer::currentTime() const {
    float value;
    NapiHelper::napiCallFunction("currentTime", &value);
    return value;
}

float VideoPlayer::duration() const {
    float value;
    NapiHelper::napiCallFunction("duration", &value);
    return value;
}

void VideoPlayer::getFrame() {
	// todo openharmony cannot support
}

int VideoPlayer::getFrameChannel() const {
    // todo openharmony cannot support
    return -1;
}

int VideoPlayer::getFrameWidth() const {
    int32_t value;
    NapiHelper::napiCallFunction("getFrameWidth", &value);
    return value;
}

int VideoPlayer::getFrameHeight() const {
    int32_t value;
    NapiHelper::napiCallFunction("getFrameHeight", &value);
    return value;
}

int VideoPlayer::getVideoTexDataSize() const {
    // todo openharmony cannot support
    return -1;
}

void VideoPlayer::pushFrameDataToTexture2D(cocos2d::renderer::Texture* tex) const {
    // todo openharmony cannot support
}

void VideoPlayer::setShowRawFrame(bool show) const {
    // todo openharmony cannot support
}

void VideoPlayer::update() {
    //test
}


NS_CC_END

#endif
