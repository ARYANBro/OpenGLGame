#include <Engine/Graphics/Texture.h>

#include <stb_image.h>
#include <glad/glad.h>

#include <stdexcept>

Engine::Texture::Texture()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
}

Engine::Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

void Engine::Texture::Load(const std::string& filePath)
{
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);
    if (!data)
        throw TextureLoadError("Couldn't open texture path, " + filePath);

    GLenum internalFormat;
    GLenum format;

    switch (m_Channels)
    {
        case 1:
            internalFormat = GL_R8;
            format = GL_RED;
            break;
        case 2:
            internalFormat = GL_RG8;
            format = GL_RG;
            break;
        case 3:
            internalFormat = GL_RGB16;
            format = GL_RGB;
            break;
        case 4:
            internalFormat = GL_RGBA16;
            format = GL_RGBA;
    }

    glTextureStorage2D(m_ID, 1, internalFormat, m_Width, m_Height);
    glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Engine::Texture::Bind(int slot)
{
    glBindTextureUnit(slot, m_ID);
}

void Engine::Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}