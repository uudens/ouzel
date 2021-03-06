// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#import "MetalView.h"
#include "Engine.h"
#include "Window.h"
#include "Utils.h"

using namespace ouzel;

@interface ViewDelegate: NSObject<MTKViewDelegate>

@end

@implementation ViewDelegate

-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    sharedEngine->getWindow()->setSize(Size2(size.width, size.height));
}

-(void)drawInMTKView:(nonnull MTKView*)view
{
    if (!sharedEngine->run())
    {
        [view.window close];
    }
}

@end

@implementation MetalView
{
    id<MTKViewDelegate> viewDelegate;
}

-(id)initWithFrame:(CGRect)frameRect
{
    if (self = [super initWithFrame:frameRect])
    {
        viewDelegate = [[ViewDelegate alloc] init];
        self.delegate = viewDelegate;
    }

    return self;
}

-(void)dealloc
{
    [self close];
    [super dealloc];
}

-(BOOL)canBecomeFirstResponder
{
    return YES;
}

-(void)close
{
    if (viewDelegate)
    {
        [viewDelegate release];
        viewDelegate = Nil;
        self.delegate = Nil;
    }
}

@end
