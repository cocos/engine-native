/****************************************************************************
Copyright (c) 2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

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
#define LOG_TAG "AudioDecoderManager"

#include "audio/oalsoft/AudioDecoderManager.h"
#include "audio/oalsoft/AudioDecoderMp3.h"
#include "audio/oalsoft/AudioDecoderOgg.h"
#if CC_PLATFORM == CC_PLATFORM_OHOS
    #include "audio/ohos//AudioDecoderWav.h"
#endif
#include "audio/oalsoft/AudioMacros.h"
#include "platform/FileUtils.h"

namespace cc {

static bool __mp3Inited = false;

bool AudioDecoderManager::init() {
    return true;
}

void AudioDecoderManager::destroy() {
    AudioDecoderMp3::destroy();
}

AudioDecoder *AudioDecoderManager::createDecoder(const char *path) {
    std::string suffix = FileUtils::getInstance()->getFileExtension(path);
    if (suffix == ".ogg") {
        return new (std::nothrow) AudioDecoderOgg();
    } else if (suffix == ".mp3") {
        return new (std::nothrow) AudioDecoderMp3();
    }
#if CC_PLATFORM == CC_PLATFORM_OHOS
    else if (suffix == ".wav") {
        return new (std::nothrow) AudioDecoderWav();
    }
#endif

    return nullptr;
}

void AudioDecoderManager::destroyDecoder(AudioDecoder *decoder) {
    delete decoder;
}

} // namespace cc
