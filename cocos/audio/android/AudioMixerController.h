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

#include "audio/android/utils/Errors.h"
#include "platform/CCPlatformConfig.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>

#if CC_TARGET_PLATFORM == CC_PLATFORM_OPENHARMONY
// for openharmony platform, buffer size is 4458 in normal latency mode, 240 in fast latency mode
#define MAX_AUDIO_BUFFER_SIZE 4458
#endif

namespace cocos2d { 

class Track;
class AudioMixer;

class AudioMixerController
{
public:

    struct OutputBuffer
    {
        void* buf;
        size_t size;
    };
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AudioMixerController(int bufferSizeInFrames, int sampleRate, int channelCount);
    bool init();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_OPENHARMONY
    AudioMixerController(int sampleRate, int channelCount);
    void updateBufferSize(int bufferSize);
    bool init(int bufferSizeInFrames);
#endif

    ~AudioMixerController();

    bool addTrack(Track* track);
    bool hasPlayingTacks();

    void pause();
    void resume();
    inline bool isPaused() const { return _isPaused; };

    void mixOneFrame();

    inline OutputBuffer* current() { return &_mixingBuffer; }

private:
    void destroy();
    void initTrack(Track* track, std::vector<Track*>& tracksToRemove);

private:
    int _bufferSizeInFrames;
    int _sampleRate;
    int _channelCount;

    AudioMixer* _mixer;

    std::mutex _activeTracksMutex;
    std::vector<Track*> _activeTracks;

    OutputBuffer _mixingBuffer;

    std::atomic_bool _isPaused;
    std::atomic_bool _isMixingFrame;
};

} // namespace cocos2d { 
