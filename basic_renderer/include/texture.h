#pragma once

#include <gl/glew.h>
#include <iostream>

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    void bind(unsigned int slot = 0);
    void unbind();

    inline int get_width() const
    {
        return _width;
    }
    inline int get_height() const
    {
        return _height;
    }
private:
    unsigned int _renderer_id;
    std::string _filepath;
    unsigned char* _local_buffer;
    int _width, _height, _BPP;
};