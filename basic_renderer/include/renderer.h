#pragma once

#include <gl/glew.h>

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer
{
public:
    void clear() const;
    void draw(const Vertex_array& vertex_array, const Index_buffer& index_buffer, const Shader& shader) const;
};