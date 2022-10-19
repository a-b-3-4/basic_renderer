#include <loga/log.h>

#include "renderer.h"

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const Vertex_array& vertex_array, const Index_buffer& index_buffer, const Shader& shader, uint32_t index_count) const
{
    shader.bind();
    vertex_array.bind();
    index_buffer.bind();
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}