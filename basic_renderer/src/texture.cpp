#include "texture.h"

#include "stb_image/stb_image.h"
#include <gl/glew.h>
#include <iostream>

Texture::Texture(const std::string& filepath)
: _renderer_id(0), _filepath(filepath), _local_buffer(nullptr), _width(0), _height(0), _BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    _local_buffer = stbi_load(filepath.c_str(), &_width, &_height, &_BPP, 4);

    glGenTextures(1, &_renderer_id);

    glBindTexture(GL_TEXTURE_2D, _renderer_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _local_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(_local_buffer)
        stbi_image_free(_local_buffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_renderer_id);
}

void Texture::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _renderer_id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}