#pragma once

#include <vector>
#include <gl/glew.h>

struct Vertex_buffer_element
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        return 0;
    }
};


class Vertex_buffer_layout
{
public:
    Vertex_buffer_layout()
    : _stride(0)
    {}

    template<typename T>
    void push(unsigned int count)
    {
        static_assert(false);
    }
    template<>
    void push<float>(unsigned int count)
    {
        _elements.push_back({ GL_FLOAT, count, GL_FALSE });
        _stride += count * Vertex_buffer_element::get_size_of_type(GL_FLOAT);
    }
    template<>
    void push<unsigned int>(unsigned int count)
    {
        _elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        _stride += count * Vertex_buffer_element::get_size_of_type(GL_UNSIGNED_INT);
    }
    template<>
    void push<unsigned char>(unsigned int count)
    {
        _elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        _stride += count * Vertex_buffer_element::get_size_of_type(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<Vertex_buffer_element>& get_elements() const
    {
        return _elements;
    }
    inline unsigned int get_stride() const
    {
        return _stride;
    }
private:
    std::vector<Vertex_buffer_element> _elements;
    unsigned int _stride;
};