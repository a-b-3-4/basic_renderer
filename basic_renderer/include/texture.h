#pragma once

#include <iostream>

class Texture
{
public:
    Texture(const std::string& filepath);
    Texture(uint32_t color);
    ~Texture();

    void bind_texture_unit(const unsigned int unit);
    
    void bind(unsigned int slot = 0);
    void unbind();

    bool operator==(const Texture texture) const;
    void operator=(const Texture texture);

    inline int get_width() const
    {
        return _width;
    }
    inline int get_height() const
    {
        return _height;
    }
    inline unsigned int get_texture_id() const
    {
        return _renderer_id;
    }

private:
    unsigned int _renderer_id;
    std::string _filepath;
    unsigned char* _local_buffer;
    int _width;
    int _height;
    int _BPP;
};