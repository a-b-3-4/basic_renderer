#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class Vertex_array
{
private:
    unsigned int m_renderer_id;
public:
    Vertex_array();
    ~Vertex_array();

    void add_buffer(const Vertex_buffer& vertex_buffer, const Vertex_buffer_layout& vertex_buffer_layout);

    void bind() const;
    void unbind() const;
};