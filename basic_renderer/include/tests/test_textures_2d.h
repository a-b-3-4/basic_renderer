#pragma once

#include <memory>

#include "tests/test.h"

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"
#include "texture.h"

namespace test
{
    class Test_textures_2d : public Test
    {
    public:
        Test_textures_2d();
        ~Test_textures_2d();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_ImGui_render() override;
    private:
        std::unique_ptr<Vertex_array> _vertex_array;
        std::unique_ptr<Vertex_buffer> _vertex_buffer;
        std::unique_ptr<Index_buffer> _index_buffer;
        std::unique_ptr<Shader> _shader;
        std::unique_ptr<Texture> _texture;

        glm::vec3 _translation_a;
        glm::vec3 _translation_b;
        
        glm::mat4 _projection;
        glm::mat4 _view;
    };
}