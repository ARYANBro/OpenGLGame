#pragma once

#include <unordered_set>

#include <glm/glm.hpp>

namespace Engine
{
    enum class MouseButton
    {
        Left,
        Right
    };

    class InputSystem
    {
    public:
        InputSystem();
        ~InputSystem() noexcept {}

        void AddListener(class InputListener* listener);
        bool RemoveListener(class InputListener* listener);
        void Update();

    private:
        std::unordered_set<InputListener*> m_Listeners;
        unsigned char m_KeyStates[256] = {};
        unsigned char m_PreviousKeyStates[256] = {};
        unsigned char m_MouseState[2] = {};
        unsigned char m_PrevMouseState[2] = {};
        glm::vec2 m_PrevMouseLoc;

    private:
        void ProcessMouseMovement() noexcept;
        void ProcessKeyboardInput() noexcept;
        void ProcessMouseInput() noexcept;
    };
}