// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <set>
#include <map>
#include <dispatch/dispatch.h>

#if defined(__OBJC__)
#import <Metal/Metal.h>
#import <MetalKit/MTKView.h>
typedef MTKView* MTKViewPtr;
typedef id<MTLDevice> MTLDevicePtr;
typedef MTLRenderPassDescriptor* MTLRenderPassDescriptorPtr;
typedef id<MTLSamplerState> MTLSamplerStatePtr;
typedef id<MTLCommandQueue> MTLCommandQueuePtr;
typedef id<MTLRenderPipelineState> MTLRenderPipelineStatePtr;
typedef id<MTLCommandBuffer> MTLCommandBufferPtr;
typedef id<MTLRenderCommandEncoder> MTLRenderCommandEncoderPtr;
typedef id <MTLTexture> MTLTexturePtr;
#else
#include <objc/objc.h>
typedef id MTKViewPtr;
typedef id MTLDevicePtr;
typedef id MTLRenderPassDescriptorPtr;
typedef id MTLSamplerStatePtr;
typedef id MTLCommandQueuePtr;
typedef id MTLRenderPipelineStatePtr;
typedef id MTLCommandBufferPtr;
typedef id MTLRenderCommandEncoderPtr;
typedef id MTLTexturePtr;
#endif

#include "graphics/Renderer.h"

namespace ouzel
{
    class Engine;

    namespace graphics
    {
        class BlendStateMetal;
        class ShaderMetal;

        class RendererMetal: public Renderer
        {
            friend Engine;
        public:
            static bool available();

            virtual ~RendererMetal();
            virtual void free() override;

            virtual void setClearColor(Color newColor) override;

            virtual void setSize(const Size2& newSize) override;

            virtual void clear() override;
            virtual void present() override;

            virtual std::vector<Size2> getSupportedResolutions() const override;

            virtual TexturePtr createTexture(const Size2& textureSize, bool dynamic, bool mipmaps = true) override;
            virtual TexturePtr loadTextureFromFile(const std::string& filename, bool dynamic, bool mipmaps = true) override;
            virtual TexturePtr loadTextureFromData(const void* data, const Size2& size, bool dynamic, bool mipmaps = true) override;

            virtual RenderTargetPtr createRenderTarget(const Size2& size, bool depthBuffer) override;
            virtual bool activateRenderTarget(const RenderTargetPtr& renderTarget) override;

            virtual ShaderPtr loadShaderFromFiles(const std::string& pixelShader,
                                                  const std::string& vertexShader,
                                                  uint32_t vertexAttributes,
                                                  const std::string& pixelShaderFunction = "",
                                                  const std::string& vertexShaderFunction = "") override;
            virtual ShaderPtr loadShaderFromBuffers(const uint8_t* pixelShader,
                                                    uint32_t pixelShaderSize,
                                                    const uint8_t* vertexShader,
                                                    uint32_t vertexShaderSize,
                                                    uint32_t vertexAttributes,
                                                    const std::string& pixelShaderFunction = "",
                                                    const std::string& vertexShaderFunction = "") override;

            virtual MeshBufferPtr createMeshBuffer() override;
            virtual MeshBufferPtr createMeshBufferFromData(const void* indices, uint32_t indexSize, uint32_t indexCount, bool dynamicIndexBuffer, const void* vertices, uint32_t vertexAttributes, uint32_t vertexCount, bool dynamicVertexBuffer) override;
            virtual bool drawMeshBuffer(const MeshBufferPtr& meshBuffer, uint32_t indexCount = 0, DrawMode drawMode = DrawMode::TRIANGLE_LIST, uint32_t startIndex = 0) override;

            virtual void activateScissorTest(const Rectangle& rectangle) override;

            virtual bool saveScreenshot(const std::string& filename) override;

            MTLDevicePtr getDevice() const { return device; }
            MTKViewPtr getMetalView() const { return view; }

        protected:
            RendererMetal();

            virtual bool init(const WindowPtr& window,
                              uint32_t newSampleCount,
                              TextureFiltering newTextureFiltering,
                              float newTargetFPS,
                              bool newVerticalSync) override;

            MTLRenderPipelineStatePtr createPipelineState(const std::shared_ptr<BlendStateMetal>& blendState,
                                                          const std::shared_ptr<ShaderMetal>& shader);

            bool createRenderCommandEncoder(MTLRenderPassDescriptorPtr newRenderPassDescriptor);

            MTKViewPtr view = Nil;

            MTLDevicePtr device = Nil;
            MTLRenderPassDescriptorPtr renderPassDescriptor = Nil;
            std::set<MTLRenderPassDescriptorPtr> clearedRenderPassDescriptors;

            MTLSamplerStatePtr samplerState = Nil;
            MTLCommandQueuePtr commandQueue = Nil;

            MTLTexturePtr msaaTexture = Nil;

            MTLCommandBufferPtr currentCommandBuffer = Nil;

            MTLRenderPassDescriptorPtr currentRenderPassDescriptor = Nil;
            MTLRenderCommandEncoderPtr currentRenderCommandEncoder = Nil;

            dispatch_semaphore_t inflightSemaphore;

            std::map<std::pair<std::shared_ptr<BlendStateMetal>, std::shared_ptr<ShaderMetal>>, MTLRenderPipelineStatePtr> pipelineStates;
        };
    } // namespace graphics
} // namespace ouzel
