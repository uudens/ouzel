// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "scene/Drawable.h"
#include "utils/Types.h"
#include "math/Size2.h"
#include "graphics/MeshBuffer.h"
#include "math/Rectangle.h"
#include "scene/SpriteFrame.h"

namespace ouzel
{
    namespace scene
    {
        class SceneManager;

        class Sprite: public Drawable
        {
        public:
            static SpritePtr createFromSpriteFrames(const std::vector<SpriteFramePtr>& spriteFrames);
            static SpritePtr createFromFile(const std::string& filename, bool mipmaps = true);

            Sprite();
            virtual ~Sprite();

            virtual bool initFromSpriteFrames(const std::vector<SpriteFramePtr>& spriteFrames);
            virtual bool initFromFile(const std::string& filename, bool mipmaps = true);

            virtual void update(float delta);
            virtual void draw(const Matrix4& projectionMatrix, const Matrix4& transformMatrix, const graphics::Color& drawColor) override;

            virtual graphics::ShaderPtr getShader() const { return shader; }
            virtual void setShader(const graphics::ShaderPtr& newShader);

            virtual const Size2& getSize() const { return size; }

            virtual void play(bool pRepeat = true, float newFrameInterval = 0.1f);
            virtual void stop(bool resetAnimation = true);
            virtual void reset();
            virtual bool isPlaying() const { return playing; }

        protected:
            graphics::ShaderPtr shader;
            graphics::BlendStatePtr blendState;

            Size2 size;

            std::vector<SpriteFramePtr> frames;

            uint32_t currentFrame = 0;
            float frameInterval = 0.0f;
            bool playing = false;
            bool repeat = false;
            float timeSinceLastFrame = 0.0f;

            UpdateCallbackPtr updateCallback;
        };
    } // namespace scene
} // namespace ouzel
