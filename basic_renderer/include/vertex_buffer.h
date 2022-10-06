#pragma once

class Vertex_buffer
{
private:
    unsigned int m_renderer_id;
public:
    Vertex_buffer(const void* data, unsigned int size);
    ~Vertex_buffer();

    void bind() const;
    void unbind() const;
};