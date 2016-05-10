// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <vector>
#include "Animator.h"
#include "Vector2.h"

namespace ouzel
{
    namespace scene
    {
        class Shake: public Animator
        {
        public:
            Shake(float pLength, const Vector2& pDistance, float pTimeScale);

            void start(Node* targetNode) override;

        protected:
            virtual void updateProgress() override;

            uint32_t seedX;
            uint32_t seedY;
            Vector2 distance;
            float timeScale;
            Vector2 startPosition;
        };
    } // namespace scene
} // namespace ouzel
