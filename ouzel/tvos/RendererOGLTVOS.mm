// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "RendererOGLTVOS.h"
#include "core/Engine.h"
#include "WindowTVOS.h"
#include "utils/Utils.h"

namespace ouzel
{
    namespace graphics
    {
        RendererOGLTVOS::~RendererOGLTVOS()
        {
            if (context)
            {
                if ([EAGLContext currentContext] == context)
                {
                    [EAGLContext setCurrentContext:nil];
                }
                [context release];
            }

            if (frameBufferId)
            {
                glDeleteFramebuffers(1, &frameBufferId);
            }

            if (colorRenderBuffer)
            {
                glDeleteRenderbuffers(1, &colorRenderBuffer);
            }
        }

        void RendererOGLTVOS::free()
        {
            if (context)
            {
                if ([EAGLContext currentContext] == context)
                {
                    [EAGLContext setCurrentContext:nil];
                }
                [context release];
            }

            if (frameBufferId)
            {
                glDeleteFramebuffers(1, &frameBufferId);
                frameBufferId = 0;
            }

            if (colorRenderBuffer)
            {
                glDeleteRenderbuffers(1, &colorRenderBuffer);
                colorRenderBuffer = 0;
            }
        }

        bool RendererOGLTVOS::init(const WindowPtr& window,
                                   uint32_t newSampleCount,
                                   TextureFiltering newTextureFiltering,
                                   float newTargetFPS,
                                   bool newVerticalSync)
        {
            free();

            UIView* view = std::static_pointer_cast<WindowTVOS>(sharedEngine->getWindow())->getNativeView();

            CAEAGLLayer* eaglLayer = (CAEAGLLayer*)view.layer;
            eaglLayer.opaque = YES;
            eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                            [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

            context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];

            if (context)
            {
                apiVersion = 3;
                log("Using OpenGL ES 3");
            }
            else
            {
                log("Failed to create OpenGL ES 3 rendering context");

                context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

                if (context)
                {
                    apiVersion = 2;
                    log("Using OpenGL ES 2");
                }
                else
                {
                    ouzel::log("Failed to initialize OpenGL ES 2 rendering context");
                    return false;
                }
            }

            if (![EAGLContext setCurrentContext:context])
            {
                ouzel::log("Failed to set current OpenGL rendering context");
                return false;
            }

            // render buffer
            glGenRenderbuffers(1, &colorRenderBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
            [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];

            GLint frameBufferWidth;
            GLint frameBufferHeight;
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &frameBufferWidth);
            glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &frameBufferHeight);

            // frame buffer
            glGenFramebuffers(1, &frameBufferId);
            graphics::RendererOGL::bindFrameBuffer(frameBufferId);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                      GL_RENDERBUFFER, colorRenderBuffer);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                log("Failed to create framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
                return false;
            }

            window->setSize(Size2(static_cast<float>(frameBufferWidth),
                                  static_cast<float>(frameBufferHeight)));

            return RendererOGL::init(window, newSampleCount, newTextureFiltering, newTargetFPS, newVerticalSync);
        }

        void RendererOGLTVOS::clear()
        {
            if (![EAGLContext setCurrentContext:context])
            {
                ouzel::log("Failed to set current OpenGL context");
            }

            RendererOGL::clear();
        }

        void RendererOGLTVOS::present()
        {
            RendererOGL::present();

            [context presentRenderbuffer:GL_RENDERBUFFER];
        }
    } // namespace graphics
} // namespace ouzel
