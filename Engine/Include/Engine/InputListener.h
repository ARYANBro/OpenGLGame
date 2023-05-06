#pragma once

#include "Math/MathTypes.h"

namespace Engine
{
    class InputListener
    {
    public:
        InputListener() noexcept = default;
        virtual ~InputListener() noexcept = default;

        virtual void OnKeyDown(int key) = 0;
        virtual void OnKeyUp(int key) = 0;
        virtual void OnMouseMove(const Math::Vector2& deltaMousePos) = 0;
    };
}