#include <Engine/Window.h>

#include <Engine/Math/Rectangle.h>
#include <Engine/Debug.h>
#include <Engine/Game.h>

#include <glad/glad.h>
#include <glad/glad_wgl.h>

#include <cassert>
#include <stdexcept>

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_SETFOCUS:
        {
            Engine::Window* window = reinterpret_cast<Engine::Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            window->OnFocus();
            break;
        }

        case WM_KILLFOCUS:
        {
            Engine::Window* window = reinterpret_cast<Engine::Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            window->OnLooseFocus();
            break;
        }
        
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
        break;
    }

    return NULL;
}

Engine::Window::Window(const std::wstring& windowName, int width, int height)
    : m_Width(width), m_Height(height)
{
    Init(windowName, width, height);
}

void Engine::Window::Init(const std::wstring& windowName, int width, int height)
{
    const wchar_t className[] = L"E_Window";

    WNDCLASSEX win = {};
    win.cbSize = sizeof(WNDCLASSEX);
    win.lpszClassName = className;
    win.lpfnWndProc = WndProc;

    auto classID = RegisterClassEx(&win);
    assert(classID);

    RECT rect = { 0, 0, width, height };
    DWORD winStyle = WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU;
    
    AdjustWindowRect(&rect, winStyle, false);

    m_Handle = CreateWindowEx(
        NULL,
        className,
        windowName.c_str(),
        winStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        NULL,
        NULL
    );

    if (!m_Handle)
        throw std::runtime_error("Engine::Window::Window(const std::wstring& windowName, int width, int height) | Failed to create a window");


    SetWindowLongPtr(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    ShowWindow(m_Handle, SW_SHOW);
    UpdateWindow(m_Handle);
}
 
Engine::Window::~Window() noexcept
{
    DestroyWindow(m_Handle);
}

Math::Rectangle Engine::Window::GetViewportSize()
{
    RECT rect;
    GetClientRect(m_Handle, &rect);
    return { rect.right - rect.left, rect.bottom - rect.top };
}

void Engine::Window::OnFocus()
{
    Game::Get().GetInputSystem().AddListener(&Game::Get());
}

void Engine::Window::OnLooseFocus()
{
    Game::Get().GetInputSystem().RemoveListener(&Game::Get());
}