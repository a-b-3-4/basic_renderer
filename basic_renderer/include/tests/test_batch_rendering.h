#pragma once

#include <memory>

#include "tests/test.h"

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"
#include "texture.h"

namespace test
{
    class Test_batch_rendering : public Test
    {
    public:
        Test_batch_rendering();
        ~Test_batch_rendering();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_ImGui_render() override;
    private:
        std::unique_ptr<Vertex_array> _vertex_array;
        std::unique_ptr<Vertex_buffer> _vertex_buffer;
        std::unique_ptr<Index_buffer> _index_buffer;
        std::unique_ptr<Shader> _shader;
        std::unique_ptr<Texture> _texture;
    };
}