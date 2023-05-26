#pragma once

#include <glm/glm.hpp>

#include <string>
#include <stdexcept>

#include <Windows.h>

namespace Engine
{
    class WindowCreationError : public std::runtime_error
    {
    public:
        WindowCreationError(const std::string& error) : std::runtime_error(error) {}
        WindowCreationError(const char* error) : std::runtime_error(error) {}
    };

    class Window
    {
    public:
        Window(const std::wstring& windowName, int width, int height);
        Window() noexcept = default;
        ~Window() noexcept;

        void Init(const std::wstring& windowName, int width, int height);

        HWND GetHandle() const noexcept { return m_Handle; }
        glm::ivec2 GetViewportSize();

        void OnFocus();
        void OnLooseFocus();

    private:
        HWND m_Handle;  
        int m_Width;
        int m_Height;
    };
}

