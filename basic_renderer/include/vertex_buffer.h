#pragma once

class Vertex_buffer
{
public:
    Vertex_buffer(unsigned int size);
    Vertex_buffer(const void* data, unsigned int size);
    ~Vertex_buffer();

    void bind() const;
    void unbind() const;
private:
    unsigned int _renderer_id;
};