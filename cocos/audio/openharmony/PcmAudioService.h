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

#pragma once

#include "audio/android/IAudioPlayer.h"
#include "audio/android/PcmData.h"
#include "audio/android/utils/Compat.h"
#include "base/CCData.h"

#include <mutex>
#include <condition_variable>
#include <ohaudio/native_audiostreambuilder.h>
#include <ohaudio/native_audiorenderer.h>

namespace cocos2d { 


class AudioMixerController;

class PcmAudioService
{
public:
    inline int getChannelCount() const { return _numChannels; };

    inline int getSampleRate() const { return _sampleRate; };


    PcmAudioService();
    virtual ~PcmAudioService();

    // openharmony platform add bufferSizeInBytes pointer param to get ohaudio buffersize, which is needed by AudioMixer.
    bool init(AudioMixerController* controller, int numChannels, int sampleRate, int* bufferSizeInBytes);
    

    void pause();
    void resume();
    
private:
    static int32_t AudioRendererOnWriteData(OH_AudioRenderer* renderer, void* userData, void* buffer, int32_t bufferLen);
    int _numChannels;
    int _sampleRate;
    int _bufferSizeInBytes;

    AudioMixerController* _controller;
    OH_AudioRenderer *_audioRenderer;
    OH_AudioStreamBuilder *_builder;

    friend class AudioPlayerProvider;
};

} // namespace cocos2d { 

