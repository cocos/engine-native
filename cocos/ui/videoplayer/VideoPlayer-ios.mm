/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.

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

#include "VideoPlayer.h"

USING_NS_CC;

// No Available on tvOS
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS && !defined(CC_TARGET_OS_TVOS)

//-------------------------------------------------------------------------------------

#import <AVKit/AVPlayerViewController.h>
#import <CoreMedia/CMTime.h>
#import <CoreVideo/CVPixelBuffer.h>

#include "platform/CCApplication.h"
#include "platform/ios/CCEAGLView-ios.h"
#include "platform/CCFileUtils.h"
#include "renderer/gfx/Texture2D.h"

@interface UIVideoViewWrapperIos : NSObject

typedef NS_ENUM(NSInteger, PlayerbackState) {
    PlayerbackStateUnknown = 0,
    PlayerbackStatePaused,
    PlayerbackStopped,
    PlayerbackStatePlaying,
    PlayerbackStateCompleted
};

@property (assign, nonatomic) AVPlayerViewController * playerController;

- (void) setFrame:(int) left :(int) top :(int) width :(int) height;
- (void) setURL:(int) videoSource :(std::string&) videoUrl;
- (void) play;
- (void) pause;
- (void) resume;
- (void) stop;
- (BOOL) isPlaying;
- (void) seekTo:(float) sec;
- (float) currentTime;
- (float) duration;
- (void) setVisible:(BOOL) visible;
- (void) setKeepRatioEnabled:(BOOL) enabled;
- (void) setFullScreenEnabled:(BOOL) enabled;
- (void) showPlaybackControls:(BOOL) value;
- (BOOL) isFullScreenEnabled;
- (void) cleanup;
-(id) init:(void*) videoPlayer;

- (unsigned char*) getFrame;
- (bool) copyFinished;
- (int) getFrameWidth;
- (int) getFrameHeight;
- (int) getFrameDataSize;
- (int) getBitCount;
- (void) setShowRaw:(BOOL) show;
- (void) clearBuffers;

-(void) videoFinished:(NSNotification*) notification;

@end

@implementation UIVideoViewWrapperIos
{
    int _left;
    int _top;
    int _width;
    int _height;
    bool _keepRatioEnabled;
    bool _fullscreen;
    CGRect _restoreRect;
    PlayerbackState _state;
    VideoPlayer* _videoPlayer;
    
    int _frameWidth;
    int _frameHeight;
    int _frameDataSize;
    int _frameBitCount;
    unsigned char* _videoPixels;
    bool _finishCopy;
}

-(id)init:(void*)videoPlayer
{
    if (self = [super init]) {
        _keepRatioEnabled = FALSE;
        _left = _top = _width = _height = 0;

        [self initPlayerController];
        _videoPlayer = (VideoPlayer*)videoPlayer;
    }

    return self;
}

-(void)initPlayerController
{
    self.playerController = [AVPlayerViewController new];
    [self setFrame:_left :_top :_width :_height];
    [self showPlaybackControls:TRUE];
    [self setKeepRatioEnabled:_keepRatioEnabled];
    _state = PlayerbackStateUnknown;
    
    _frameWidth = 0;
    _frameHeight = 0;
    _frameDataSize = 0;
    _frameBitCount = 1;
    _videoPixels = nullptr;
    _finishCopy = false;
    
    [self setShowRaw:YES];
}

-(void) dealloc
{
    if(_videoPixels != nullptr) free(_videoPixels);
    
    _videoPlayer = nullptr;
    [self cleanup];
    [super dealloc];
}

-(void) setFrame:(int)left :(int)top :(int)width :(int)height
{
    if (_left == left && _width == width && _top == top && _height == height)
        return;
    
    _left = left;
    _width = width;
    _top = top;
    _height = height;
    [self.playerController.view setFrame:CGRectMake(left, top, width, height)];
}

-(unsigned char*) getFrame
{
    UInt32 type = kCVPixelFormatType_32BGRA;
    AVPlayerItem* item = self.playerController.player.currentItem;
    if(item.outputs.count == 0) {
        NSDictionary* settings = @{ (id)kCVPixelBufferPixelFormatTypeKey : @(type) };
        AVPlayerItemVideoOutput* output = [[AVPlayerItemVideoOutput alloc] initWithPixelBufferAttributes:settings];
        [item addOutput:output];
    }
    AVPlayerItemOutput* output = item.outputs[0];
    
    CMTime time = self.playerController.player.currentTime;
    CVPixelBufferRef pixelBuffer = [output copyPixelBufferForItemTime:time itemTimeForDisplay:nil];
    
    _frameBitCount = 4;
    _frameHeight = (int)CVPixelBufferGetHeight(pixelBuffer);
    _frameWidth = (int)CVPixelBufferGetBytesPerRow(pixelBuffer) / _frameBitCount;
    _frameDataSize = (int)CVPixelBufferGetDataSize(pixelBuffer);
    
    if(_videoPixels == nullptr && _frameWidth > 0 && _frameHeight > 0) {
        _videoPixels = (unsigned char*)calloc(_frameDataSize, 1);
    }
    
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    void* pixels = CVPixelBufferGetBaseAddress(pixelBuffer);
    if(_videoPixels != nullptr && pixels != nullptr) {
        memcpy(_videoPixels, pixels, _frameDataSize);
        _finishCopy = true;
    }
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
    
    return _videoPixels;
}

-(bool) copyFinished
{
    return _finishCopy;
}

-(int) getFrameWidth
{
    return _frameWidth;
}

-(int) getFrameHeight
{
    return _frameHeight;
}

-(int) getFrameDataSize
{
    return _frameDataSize;
}

-(int) getBitCount
{
    return _frameBitCount;
}

-(void) setShowRaw:(BOOL) show
{
    if(show == YES) {
        self.playerController.view.alpha = 1;
    } else {
        self.playerController.view.alpha = 0;
    }
}

-(void) setFullScreenEnabled:(BOOL) enabled
{
    // AVPlayerViewController doesn't provide API to enable fullscreen. But you can toggle
    // fullsreen by the playback controllers.
}

-(BOOL) isFullScreenEnabled
{
    return false;
}

-(BOOL) isPlaying
{
    return (self.playerController.player && self.playerController.player.rate != 0);
}

-(void) setURL:(int)videoSource :(std::string &)videoUrl
{
    [self clearBuffers];
    [self cleanup];
    [self initPlayerController];

    if (videoSource == 1)
        self.playerController.player = [[[AVPlayer alloc] initWithURL:[NSURL URLWithString:@(videoUrl.c_str())]] autorelease];
    else
        self.playerController.player = [[[AVPlayer alloc] initWithURL:[NSURL fileURLWithPath:@(videoUrl.c_str())]] autorelease];

    [self registerPlayerEventListener];
}

-(void) seekTo:(float)sec
{
    if (self.playerController.player)
        [self.playerController.player seekToTime:CMTimeMake(sec * 600, 600) toleranceBefore:kCMTimeZero toleranceAfter:kCMTimeZero];

}

-(float) currentTime
{
    if (self.playerController.player)
        return CMTimeGetSeconds([self.playerController.player currentTime]);

    return -1;
}

-(float) duration
{
    if (self.playerController.player)
        return CMTimeGetSeconds(self.playerController.player.currentItem.asset.duration);

    return  -1;;
}

-(void) setVisible:(BOOL)visible
{
    [self.playerController.view setHidden:!visible];
    if (!visible)
        [self pause];
}

-(void) setKeepRatioEnabled:(BOOL)enabled
{
    _keepRatioEnabled = enabled;
    if (_keepRatioEnabled)
        self.playerController.videoGravity = AVLayerVideoGravityResizeAspectFill;
    else
        self.playerController.videoGravity = AVLayerVideoGravityResize;
}

-(void) play
{
    if (self.playerController.player && ![self isPlaying] ) {
        [self.playerController.player play];
        _state = PlayerbackStatePlaying;
        _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::PLAYING);
    }
}

-(void) pause
{
    if ( [self isPlaying] ) {
        [self.playerController.player pause];
        _state = PlayerbackStatePaused;
        _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::PAUSED);
    }
}

-(void) resume
{
    if (self.playerController.player && _state == PlayerbackStatePaused)
        [self play];
}

-(void) stop
{
    // AVPlayer doesn't have `stop` method, so just pause it, and seek time to 0.
    if (self.playerController.player && _state != PlayerbackStopped) {
        [self seekTo:0];
        [self.playerController.player pause];
        _state = PlayerbackStopped;

        // stop() will be invoked in dealloc, which is invoked by _videoPlayer's destructor,
        // so do't send the message when _videoPlayer is being deleted.
        if (_videoPlayer)
            _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::STOPPED);
    }
}

// Private functions
-(void) clearBuffers
{
    if(_videoPixels != nullptr) {
        free(_videoPixels);
        _videoPixels = nullptr;
    }
    
    AVPlayerItem* item = self.playerController.player.currentItem;
    if(item.outputs.count > 0) {
        AVPlayerItemOutput* output = item.outputs[0];
        [item removeOutput:output];
        [output dealloc];
    }
}

-(void) cleanup
{
    [self stop];
    [self removePlayerEventListener];
    [self.playerController.view removeFromSuperview];
    [self.playerController release];
}

-(void) removePlayerEventListener {
    if (self.playerController.player)
    {
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                              name:AVPlayerItemDidPlayToEndTimeNotification
                                              object:self.playerController.player.currentItem];

       [self.playerController.player removeObserver:self forKeyPath:@"status"];
    }
}

-(void) registerPlayerEventListener
{
    if (self.playerController.player)
    {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(videoFinished:)
                                                 name:AVPlayerItemDidPlayToEndTimeNotification
                                                 object:self.playerController.player.currentItem];

        [self.playerController.player addObserver:self forKeyPath:@"status" options:0 context:nil];
    }
}

-(void) showPlaybackControls:(BOOL)value
{
    self.playerController.showsPlaybackControls = value;
}

-(void) videoFinished:(NSNotification *)notification
{
    if(_videoPlayer != nullptr) {
        _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::COMPLETED);
        _state = PlayerbackStateCompleted;

        // Seek to 0 to make it playable again.
        [self seekTo:0];
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object
                        change:(NSDictionary *)change context:(void *)context {

    auto player = self.playerController.player;
    if (object == player && [keyPath isEqualToString:@"status"]) {
        if (player.status == AVPlayerStatusReadyToPlay) {
            [self addPlayerControllerSubView];
            _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::META_LOADED);
            _videoPlayer->onPlayEvent((int)VideoPlayer::EventType::READY_TO_PLAY);
        } else if (player.status == AVPlayerStatusFailed) {
            // something went wrong. player.error should contain some information
            NSLog(@"Failed to load video");
        }
    }
}

-(void)addPlayerControllerSubView {
    auto eaglview = (CCEAGLView*)cocos2d::Application::getInstance()->getView();
    [eaglview addSubview:self.playerController.view];
}

@end
//------------------------------------------------------------------------------------------------------------

VideoPlayer::VideoPlayer()
: _videoPlayerIndex(-1)
, _fullScreenEnabled(false)
, _fullScreenDirty(false)
, _keepAspectRatioEnabled(false)
{
    _videoView = [[UIVideoViewWrapperIos alloc] init:this];

#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
    
    _videoPixels = nullptr;
    _texDataSize = 0;
    _maxDataLen = 0;
}

VideoPlayer::~VideoPlayer()
{
    if(_videoView)
    {
        [((UIVideoViewWrapperIos*)_videoView) dealloc];
    }
}

void VideoPlayer::setURL(const std::string& videoUrl)
{
    if (videoUrl.find("://") == std::string::npos)
    {
        _videoURL = FileUtils::getInstance()->fullPathForFilename(videoUrl);
        _videoSource = VideoPlayer::Source::FILENAME;
    }
    else
    {
        _videoURL = videoUrl;
        _videoSource = VideoPlayer::Source::URL;
    }
    
    [((UIVideoViewWrapperIos*)_videoView) setURL:(int)_videoSource :_videoURL];
}

void VideoPlayer::setFullScreenEnabled(bool enabled)
{
    [((UIVideoViewWrapperIos*)_videoView) setFullScreenEnabled:enabled];
}

void VideoPlayer::setKeepAspectRatioEnabled(bool enable)
{
    if (_keepAspectRatioEnabled != enable)
    {
        _keepAspectRatioEnabled = enable;
        [((UIVideoViewWrapperIos*)_videoView) setKeepRatioEnabled:enable];
    }
}

void VideoPlayer::play()
{
    if (! _videoURL.empty() && _isVisible)
    {
        [((UIVideoViewWrapperIos*)_videoView) play];
    }
}

void VideoPlayer::pause()
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) pause];
    }
}

void VideoPlayer::stop()
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) stop];
    }
}

void VideoPlayer::seekTo(float sec)
{
    if (! _videoURL.empty())
    {
        [((UIVideoViewWrapperIos*)_videoView) seekTo:sec];
    }
}

float VideoPlayer::currentTime()const
{
    return [((UIVideoViewWrapperIos*)_videoView) currentTime];
}

float VideoPlayer::duration()const
{
    return [((UIVideoViewWrapperIos*)_videoView) duration];
}

void VideoPlayer::setVisible(bool visible)
{
    _isVisible = visible;

    if (!visible)
    {
        [((UIVideoViewWrapperIos*)_videoView) setVisible:NO];
    }
    else
    {
        [((UIVideoViewWrapperIos*)_videoView) setVisible:YES];
    }
}

void VideoPlayer::addEventListener(const std::string& name, const VideoPlayer::ccVideoPlayerCallback& callback)
{
    _eventCallback[name] = callback;
}

void VideoPlayer::onPlayEvent(int event)
{
    switch ((EventType)event) {
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

void VideoPlayer::setFrame(float x, float y, float width, float height)
{
    auto eaglview = (CCEAGLView*)cocos2d::Application::getInstance()->getView();
    auto scaleFactor = [eaglview contentScaleFactor];
    [((UIVideoViewWrapperIos*)_videoView) setFrame:x/scaleFactor
                                                  :y/scaleFactor
                                                  :width/scaleFactor
                                                  :height/scaleFactor];
}

void VideoPlayer::getFrame()
{
    _videoPixels = [((UIVideoViewWrapperIos*)_videoView) getFrame];
}

int VideoPlayer::getFrameChannel() const
{
    int res = VideoPlayer::PX_BGRA;
    return res;
}

int VideoPlayer::getFrameWidth() const
{
    return [((UIVideoViewWrapperIos*)_videoView) getFrameWidth];
}

int VideoPlayer::getFrameHeight() const
{
    return [((UIVideoViewWrapperIos*)_videoView) getFrameHeight];
}

int VideoPlayer::getVideoTexDataSize() const
{
    return [((UIVideoViewWrapperIos*)_videoView) getFrameDataSize];
}

void VideoPlayer::update()
{
    
}

void VideoPlayer::pushFrameDataToTexture2D(cocos2d::renderer::Texture* tex) const
{
    if(tex == nullptr) {
        printf("Can't find texture!\n");
    } else {
        bool finshCopy = [((UIVideoViewWrapperIos*)_videoView) copyFinished];
        if(_videoPixels != nullptr && getFrameWidth() > 0 && getFrameHeight() > 0 && finshCopy) {
            renderer::Texture::SubImageOption opt(0, 0, getFrameWidth(), getFrameHeight(), 0, false, false);
            opt.imageData = _videoPixels;
            ((cocos2d::renderer::Texture2D*)tex)->updateSubImage(opt);
        }
    }
}

void VideoPlayer::setShowRawFrame(bool show) const
{
    if(show)
        [((UIVideoViewWrapperIos*)_videoView) setShowRaw: YES];
    else
        [((UIVideoViewWrapperIos*)_videoView) setShowRaw: NO];
}

#endif
