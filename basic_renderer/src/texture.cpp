#include "texture.h"

#include "stb_image/stb_image.h"
#include <gl/glew.h>

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

    if(_local_buffer)
        stbi_image_free(_local_buffer);
}
Texture::Texture(uint32_t color)
: _renderer_id(0), _filepath(""), _local_buffer(nullptr), _width(0), _height(0), _BPP(0)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);

    glBindTexture(GL_TEXTURE_2D, _renderer_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_renderer_id);
}

void Texture::bind_texture_unit(const unsigned int unit)
{
    glBindTextureUnit(unit, _renderer_id);
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

bool Texture::operator==(const Texture texture) const
{
    return
    (
        this->_renderer_id  == texture._renderer_id &&
        this->_filepath     == texture._filepath &&
        this->_local_buffer == texture._local_buffer &&
        this->_width        == texture._width &&
        this->_height       == texture._height &&
        this->_BPP          == texture._BPP
    );
}
void Texture::operator=(const Texture texture)
{
    this->_renderer_id  = texture._renderer_id;
    this->_filepath     = texture._filepath;
    this->_local_buffer = texture._local_buffer;
    this->_width        = texture._width;
    this->_height       = texture._height;
    this->_BPP          = texture._BPP;
}