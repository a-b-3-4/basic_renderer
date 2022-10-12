#include <gl/glew.h>

#include "vertex_buffer.h"

Vertex_buffer::Vertex_buffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
Vertex_buffer::~Vertex_buffer()
{
    glDeleteBuffers(1, &_renderer_id);
}
void Vertex_buffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
}
void Vertex_buffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}