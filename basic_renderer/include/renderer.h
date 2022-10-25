#pragma once

#include <glm/glm.hpp>

#include "texture.h"

class Renderer
{
public:
    static void init();
    static void shutdown();

    static void begin_batch();
    static void end_batch();
    static void flush();

    static void draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void draw_quad(const glm::vec2& position, const glm::vec2& size, Texture* texture);

    //statistics
    struct Statistics
    {
        uint32_t draw_count = 0;
        uint32_t quad_count = 0;
    };

    static const Statistics& get_statistics();
    static void reset_statistics();
};