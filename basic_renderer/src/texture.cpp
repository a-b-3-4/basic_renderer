#include "texture.h"

#include "stb_image/stb_image.h"
#include <gl/glew.h>
#include <iostream>

Texture::Texture(const std::string& filepath)
: m_renderer_id(0), m_filepath(filepath), m_local_buffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_local_buffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

    glGenTextures(1, &m_renderer_id);

    glBindTexture(GL_TEXTURE_2D, m_renderer_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(m_local_buffer)
        stbi_image_free(m_local_buffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_renderer_id);
}

void Texture::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}