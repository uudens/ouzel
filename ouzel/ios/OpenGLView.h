// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface OpenGLView: UIView
{
@private
    CADisplayLink* displayLink;
}

-(id)initWithFrame:(CGRect)frameRect;

@end
