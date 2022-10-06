#pragma once

#include <gl/glew.h>
#include <iostream>

class Texture
{
private:
    unsigned int m_renderer_id;
    std::string m_filepath;
    unsigned char* m_local_buffer;
    int m_width, m_height, m_BPP;
public:
    Texture(const std::string& filepath);
    ~Texture();

    void bind(unsigned int slot = 0);
    void unbind();

    inline int get_width() const
    {
        return m_width;
    }
    inline int get_height() const
    {
        return m_height;
    }
};