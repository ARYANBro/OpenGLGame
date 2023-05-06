#include <Engine/InputSystem.h>

#include <Engine/InputListener.h>
#include <Engine/Math/Vector.h>

#include <Windows.h>
#include <algorithm>

Engine::InputSystem::InputSystem()
{
    GetCursorPos(reinterpret_cast<LPPOINT>(&m_PrevMouseLoc));
}

void Engine::InputSystem::AddListener(InputListener* listener)
{
    m_Listeners.insert(listener);
}

bool Engine::InputSystem::RemoveListener(InputListener* listener)
{
    auto it = m_Listeners.find(listener);
    if (it == m_Listeners.end())
        return false;

    m_Listeners.erase(it);
    return true;
}

void Engine::InputSystem::Update()
{
    if (m_Listeners.empty())
        return;
        
    bool result = GetKeyboardState(m_KeyStates);
    if (!result)
        return;

    POINT c;
    GetCursorPos(&c);
    Math::Vector2 currCursorPos = { static_cast<float>(c.x), static_cast<float>(c.y) };

    if (currCursorPos != m_PrevMouseLoc)
        std::ranges::for_each(m_Listeners, [deltaMousePos = currCursorPos - m_PrevMouseLoc](Engine::InputListener* listener)
        {
            listener->OnMouseMove(deltaMousePos);
        });

    m_PrevMouseLoc = currCursorPos;

    for (unsigned int i = 0; i < 256; i++)
    {
        bool keyIsDown = m_KeyStates[i] & 0x80;
        bool keyStateChanged = m_PreviousKeyStates[i] != m_KeyStates[i];

        if (keyIsDown)
            std::ranges::for_each(m_Listeners, [i](Engine::InputListener* listener) { listener->OnKeyDown(i); });
        else if (keyStateChanged) // Key is not pressed but the key state has changed that means the key has been released
            std::ranges::for_each(m_Listeners, [i](Engine::InputListener* listener) { listener->OnKeyUp(i); });
    }

    // Store the current state into the previous state
    std::memcpy(m_PreviousKeyStates, m_KeyStates, sizeof(m_PreviousKeyStates));
}