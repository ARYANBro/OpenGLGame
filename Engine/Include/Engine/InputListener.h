#pragma once

#include <glm/glm.hpp>
namespace Engine
{
    enum class MouseButton;

    class InputListener
    {
    public:
        InputListener() noexcept = default;
        virtual ~InputListener() noexcept = default;

        virtual void OnKeyDown(int key) = 0;
        virtual void OnKeyUp(int key) = 0;
        virtual void OnMouseMove(const glm::vec2& deltaMousePos) = 0;
        virtual void OnMouseUp(MouseButton button) = 0;
        virtual void OnMouseDown(MouseButton button) = 0;
    };
}