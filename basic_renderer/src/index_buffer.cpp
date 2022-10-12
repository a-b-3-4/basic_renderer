#include <gl/glew.h>

#include "index_buffer.h"

Index_buffer::Index_buffer(const unsigned int* data, unsigned int count)
: _count(count)
{
    glGenBuffers(1, &_renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}
Index_buffer::~Index_buffer()
{
    glDeleteBuffers(1, &_renderer_id);
}
void Index_buffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
}
void Index_buffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}