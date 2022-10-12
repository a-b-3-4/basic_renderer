#include <gl/glew.h>

#include "vertex_array.h"

Vertex_array::Vertex_array()
{
    glGenVertexArrays(1, &_renderer_id);
}
Vertex_array::~Vertex_array()
{
    glDeleteVertexArrays(1, &_renderer_id);
}
void Vertex_array::bind() const
{
    glBindVertexArray(_renderer_id);
}
void Vertex_array::unbind() const
{
    glBindVertexArray(0);
}
void Vertex_array::add_buffer(const Vertex_buffer& vertex_buffer, const Vertex_buffer_layout& vertex_buffer_layout)
{
    bind();
    vertex_buffer.bind();
    const auto& elements = vertex_buffer_layout.get_elements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.type, vertex_buffer_layout.get_stride(), (const void*) offset);
        offset += element.count * Vertex_buffer_element::get_size_of_type(element.type);
    }
}