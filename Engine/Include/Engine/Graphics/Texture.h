#pragma once

#include <string>

namespace Engine
{
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