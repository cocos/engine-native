#import "TestViewController.h"
#import "platform/mac/TestView.h"

@implementation TestViewController
{
    TestView* _view;
}

- (instancetype)initWithSize:(NSRect)rect {
    if (self = [super init]) {
        _view = [[TestView alloc] initWithFrame:rect];
        self.view = _view;
    }
    return self;
}

@end
