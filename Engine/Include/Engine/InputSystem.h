#pragma once

#include <Engine/Math/Vector.h>

#include <unordered_set>

namespace Engine
{
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
        Math::Vector2 m_PrevMouseLoc;
    };
}