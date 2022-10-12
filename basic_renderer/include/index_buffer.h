#pragma once

class Index_buffer
{
public:
    Index_buffer(const unsigned int* data, unsigned int count);
    ~Index_buffer();

    void bind() const;
    void unbind() const;

    inline unsigned int get_count() const
    {
        return _count;
    }
private:
    unsigned int _renderer_id;
    unsigned int _count;
};