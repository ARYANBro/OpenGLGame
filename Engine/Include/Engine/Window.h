#pragma once

#include <string>

#include <Windows.h>

#include "Math/MathTypes.h"

namespace Engine
{
    class Window
    {
    public:
        Window(const std::wstring& windowName, int width, int height);
        Window() noexcept = default;
        ~Window() noexcept;

        void Init(const std::wstring& windowName, int width, int height);

        HWND GetHandle() const noexcept { return m_Handle; }
        Math::Rectangle GetViewportSize();

        void OnFocus();
        void OnLooseFocus();

    private:
        HWND m_Handle;  
        int m_Width, m_Height;
    };
}

