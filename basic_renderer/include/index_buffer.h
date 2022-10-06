#pragma once

class Index_buffer
{
private:
    unsigned int m_renderer_id;
    unsigned int m_count;
public:
    Index_buffer(const unsigned int* data, unsigned int count);
    ~Index_buffer();

    void bind() const;
    void unbind() const;

    inline unsigned int get_count() const
    {
        return m_count;
    }
};