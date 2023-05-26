#include <Engine/InputSystem.h>

#include <Engine/InputListener.h>

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
        

    ProcessMouseMovement();
    ProcessKeyboardInput();
    ProcessMouseInput();
}

void Engine::InputSystem::ProcessMouseMovement() noexcept
{
    POINT c;
    GetCursorPos(&c);
    glm::vec2 currCursorPos = { static_cast<float>(c.x), static_cast<float>(c.y) };

    if (currCursorPos != m_PrevMouseLoc)
        std::ranges::for_each(m_Listeners, [deltaMousePos = currCursorPos - m_PrevMouseLoc](Engine::InputListener* listener)
        {
            listener->OnMouseMove(deltaMousePos);
        });

 
    m_PrevMouseLoc = currCursorPos;
}

void Engine::InputSystem::ProcessKeyboardInput() noexcept
{
    bool result = GetKeyboardState(m_KeyStates);
    if (!result)
        return;

    for (unsigned int i = 0; i < 256; i++)
    {
        bool keyIsDown = m_KeyStates[i] & 0x80;
        bool keyStateChanged = m_PreviousKeyStates[i] != m_KeyStates[i];

        if (keyIsDown)
            std::ranges::for_each(m_Listeners, [i](Engine::InputListener* listener) { listener->OnKeyDown(i); });
        else if (keyStateChanged) // Key is not pressed but the state has changed that means the key has been released
            std::ranges::for_each(m_Listeners, [i](Engine::InputListener* listener) { listener->OnKeyUp(i); });
    }

    // Store the current state into the previous state
    std::memcpy(m_PreviousKeyStates, m_KeyStates, sizeof(m_PreviousKeyStates));
}

void Engine::InputSystem::ProcessMouseInput() noexcept
{
    // Store the key
    static constexpr char s_VKKeys[2] = {
        VK_LBUTTON,
        VK_RBUTTON
    };

    for (int i = 0; i < 2; i++)
    {
        m_MouseState[i] = GetKeyState(s_VKKeys[i]);
        bool keyIsDown = m_MouseState[i] & 0x80;
        bool keyStateChanged = m_PrevMouseState[i] != m_MouseState[i];

        if (keyIsDown)
        {
            for (Engine::InputListener* listener : m_Listeners)
                listener->OnMouseDown(i == 0 ? MouseButton::Left : MouseButton::Right);
        }
        else if (keyStateChanged)
        {
            for (Engine::InputListener* listener : m_Listeners)
                listener->OnMouseUp(i == 0 ? MouseButton::Left : MouseButton::Right);
        }
    }

    std::memcpy(m_PrevMouseState, m_MouseState, sizeof(m_PrevMouseState)); // Store the current state into the previous state (for next frame)
}