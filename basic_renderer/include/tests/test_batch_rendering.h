#pragma once

#include "tests/test.h"

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
        std::unique_ptr<Shader> _shader;

        std::unique_ptr<Texture> _sample_texture_1;
        std::unique_ptr<Texture> _sample_texture_2;
        glm::vec2 _quad_position = { -1.5f, -0.5f };
    };
}