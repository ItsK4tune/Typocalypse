#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

Texture::Texture()
    : m_ID(0), m_Width(0), m_Height(0), m_Data(nullptr) {}

Texture::Texture(const std::string& fileName)
    : m_ID(0), m_Width(0), m_Height(0), m_Data(nullptr)
{
    LoadFromFile(fileName);
}

Texture::~Texture()
{
    if (m_Data)
        stbi_image_free(m_Data);
    if (m_ID)
        glDeleteTextures(1, &m_ID);
}

bool Texture::LoadFromFile(const std::string& fileName)
{
    stbi_set_flip_vertically_on_load(true);
    int channels;
    m_Data = stbi_load(fileName.c_str(), &m_Width, &m_Height, &channels, 0);
    if (!m_Data)
    {
        std::cerr << "[Texture] Failed to load image: " << fileName << std::endl;
        return false;
    }

    GLenum format;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;
    else
    {
        std::cerr << "[Texture] Unsupported channel count: " << channels << std::endl;
        stbi_image_free(m_Data);
        m_Data = nullptr;
        return false;
    }

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture::BindToUnit(GLuint unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
