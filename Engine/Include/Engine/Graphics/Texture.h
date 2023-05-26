#pragma once

#include <string>
#include <stdexcept>

namespace Engine
{
    class TextureLoadError : public std::runtime_error
    {
    public:
        TextureLoadError(const std::string& message) : std::runtime_error(message) {}
        TextureLoadError(const char* message) : std::runtime_error(message) {}
    };

    class Texture
    {
    public:
        Texture();
        ~Texture() noexcept;
        void Load(const std::string& filePath);
        void Bind(int slot = 0);
        void Unbind();
        
    private:
        unsigned int m_ID = 0;

        int m_Width = 0, m_Height = 0;
        int m_Channels = 0;
    };
}