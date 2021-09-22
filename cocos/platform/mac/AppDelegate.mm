#import "AppDelegate.h"
#include <string>
//#import "Game.h"
#import "ViewController.h"
#include "platform/mac/MacPlatform.h"
#include "cocos/bindings/event/EventDispatcher.h"

@interface AppDelegate () {
    NSWindow* _window;
//    Game*     _game;
    cc::MacPlatform* platform;
}
@end

@implementation AppDelegate

- (void) createWindow:(NSString*)title xPos:(int)x yPos:(int)y width:(int)w height:(int)h {
    
    _window.title = title;
    NSRect rect = NSMakeRect(x, y, w, h);
    _window     = [[NSWindow alloc] initWithContentRect:rect
                                          styleMask:NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
    if (!_window) {
        NSLog(@"Failed to allocated the window.");
        return;
    }
    ViewController* viewController = [[ViewController alloc] initWithSize:rect];
    _window.contentViewController  = viewController;
    _window.contentView            = viewController.view;
    [_window.contentView setWantsBestResolutionOpenGLSurface:YES];
    [_window makeKeyAndOrderFront:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowWillMiniaturizeNotification)
                                                 name:NSWindowWillMiniaturizeNotification
                                               object:_window];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowDidDeminiaturizeNotification)
                                                 name:NSWindowDidDeminiaturizeNotification
                                               object:_window];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowWillCloseNotification)
                                                 name:NSWindowWillCloseNotification
                                               object:_window];
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification {
    platform = (cc::MacPlatform*)cc::BasePlatform::getPlatform();
    platform->main(0, nullptr);
}

- (void)windowWillMiniaturizeNotification {
    platform->onPause();
}

- (void)windowDidDeminiaturizeNotification {
    platform->onResume();
}

- (void)windowWillCloseNotification {
    platform->onClose();
}

- (NSWindow*)getWindow {
    return _window;
}

- (void)applicationWillTerminate:(NSNotification*)aNotification {
//    delete _game;
    //FIXME: will crash if relase it here.
    // [_window release];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication {
    return YES;
}

- (void)dispatchEvent:(const cc::OSEvent&) ev {
    if(platform)
       platform->dispatchEvent(ev);
}

@end
