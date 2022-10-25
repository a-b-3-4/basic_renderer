#include <loga/log.h>

#include <array>

#include "renderer.h"
#include "texture.h"
#include "vertex_array.h"
#include "index_buffer.h"

static const size_t max_quad_count = 10000;
static const size_t max_vertex_count = max_quad_count * 4;
static const size_t max_index_count = max_quad_count * 6;
static const size_t max_textures = 32; //TODO: get this information from driver

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture_coordiante;
    float texture_index;
};

struct Renderer_data
{
    std::unique_ptr<Vertex_array> quad_vertex_array;
    std::unique_ptr<Vertex_buffer> quad_vertex_buffer;
    std::unique_ptr<Index_buffer> quad_index_buffer;
    
    Texture* white_texture;

    uint32_t index_count = 0;

    Vertex* quad_buffer = nullptr;
    Vertex* quad_buffer_pointer = nullptr;

    std::array<Texture*, max_textures> texture_slots;
    /*NOTE: dear future me, please forgive me, if you are reading this, trying to find out why things are breaking.
    i would guess the reason is, that we are setting every texture* in the array to point at the texture in input at the Renderer::draw_quad() funktion. this means (i think), that when you destroy the original texture, the
    pointer in the array will point at random memory, which should mess things up pretty badly. but hey, it's just a guess!*/
    uint32_t texture_slot_index = 1;

    Renderer::Statistics renderer_statistics;
};

Renderer_data _data;

void Renderer::init()
{
    _data.quad_buffer = new Vertex[max_vertex_count];
    _data.quad_vertex_array = std::make_unique<Vertex_array>();
    _data.quad_vertex_buffer = std::make_unique<Vertex_buffer>(max_vertex_count * sizeof(Vertex));

    Vertex_buffer_layout vertex_buffer_layout;
    vertex_buffer_layout.push<float>(3); //position
    vertex_buffer_layout.push<float>(4); //color
    vertex_buffer_layout.push<float>(2); //texture coordiante
    vertex_buffer_layout.push<float>(1); //texture id
    _data.quad_vertex_array->add_buffer(*_data.quad_vertex_buffer, vertex_buffer_layout);
    
    //autogenerate indecies 
    
    uint32_t indecies[max_index_count];
    uint32_t offset = 0;
    for(size_t i = 0; i < max_index_count; i += 6)
    {
        indecies[i + 0] = 0 + offset;
        indecies[i + 1] = 1 + offset;
        indecies[i + 2] = 2 + offset;

        indecies[i + 3] = 2 + offset;
        indecies[i + 4] = 3 + offset;
        indecies[i + 5] = 0 + offset;

        offset += 4;
    }

    _data.quad_index_buffer = std::make_unique<Index_buffer>(indecies, sizeof(indecies)/sizeof(unsigned int));

    // 1x1 white texture
    uint32_t color = 0xffffffff;
    _data.white_texture = new Texture(color);

    _data.texture_slots[0] = _data.white_texture;

    for(size_t i = 1; i < max_textures; i++)
    {
        _data.texture_slots[i] = nullptr;
    }
}
void Renderer::shutdown()
{
    delete[] _data.quad_buffer;
}

void Renderer::begin_batch()
{
    _data.quad_buffer_pointer = _data.quad_buffer;
}
void Renderer::end_batch()
{
    ptrdiff_t size = (uint8_t*)_data.quad_buffer_pointer - (uint8_t*)_data.quad_buffer;
    _data.quad_vertex_buffer->bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, _data.quad_buffer);
}
void Renderer::flush()
{
    for(uint32_t i = 0; i < _data.texture_slot_index; i++)
    {
        _data.texture_slots[i]->bind_texture_unit(i);
    }

    _data.quad_vertex_array->bind();
    glDrawElements(GL_TRIANGLES, _data.index_count, GL_UNSIGNED_INT, nullptr);
    _data.renderer_statistics.draw_count++;

    _data.index_count = 0;
    _data.texture_slot_index = 1;
}

void Renderer::draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    if(_data.index_count >= max_index_count)
    {
        end_batch();
        flush();
        begin_batch();
    }

    float texture_index = 0.0f;

    _data.quad_buffer_pointer->position = { position.x, position.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 0.0f, 0.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.quad_buffer_pointer->position = { position.x + size.x, position.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 0.0f, 0.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.quad_buffer_pointer->position = { position.x + size.x, position.y + size.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 0.0f, 0.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.quad_buffer_pointer->position = { position.x, position.y + size.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 0.0f, 0.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.index_count += 6;
    _data.renderer_statistics.quad_count++;
}
void Renderer::draw_quad(const glm::vec2& position, const glm::vec2& size, Texture* texture)
{
    if(_data.index_count >= max_index_count || _data.texture_slot_index > max_textures - 1)
    {
        end_batch();
        flush();
        begin_batch();
    }

    constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

    float texture_index = 0.0f;
    for(uint32_t i = 1; i < _data.texture_slot_index; i++)
    {
        if(_data.texture_slots[i]->get_texture_id() == texture->get_texture_id())
        {
            texture_index = (float)i;
            break;
        }
    }

    if(texture_index == 0.0f)
    {
        texture_index = (float)_data.texture_slot_index;
        _data.texture_slots[_data.texture_slot_index] = texture;
        _data.texture_slot_index++;
    }

    _data.quad_buffer_pointer->position = { position.x, position.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 0.0f, 0.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.quad_buffer_pointer->position = { position.x + size.x, position.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 1.0f, 0.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.quad_buffer_pointer->position = { position.x + size.x, position.y + size.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 1.0f, 1.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.quad_buffer_pointer->position = { position.x, position.y + size.y, 0.0f };
    _data.quad_buffer_pointer->color = color;
    _data.quad_buffer_pointer->texture_coordiante = { 0.0f, 1.0f };
    _data.quad_buffer_pointer->texture_index = texture_index;
    _data.quad_buffer_pointer++;

    _data.index_count += 6;
    _data.renderer_statistics.quad_count++;
}

const Renderer::Statistics& Renderer::get_statistics()
{
    return _data.renderer_statistics;
}
void Renderer::reset_statistics()
{
    memset(&_data.renderer_statistics, 0, sizeof(Statistics));
}