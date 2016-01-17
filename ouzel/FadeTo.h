// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "Animator.h"

namespace ouzel
{
    class FadeTo: public Animator
    {
    public:
        FadeTo(float length, float opacity);
        virtual void update(float delta) override;
        
        virtual void start(NodePtr const& node) override;
        
    protected:
        float _startOpacity = 0.0f;
        float _targetOpacity = 0.0f;
        float _diff = 0.0f;
    };
}
