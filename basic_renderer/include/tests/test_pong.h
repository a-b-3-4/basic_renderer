#pragma once

#include "tests/test.h"

#include "shader.h"
#include "texture.h"

namespace test
{
    class Test_pong : public Test
    {
    public:
        Test_pong();
        ~Test_pong();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_ImGui_render() override;
    private:
        std::unique_ptr<Shader> _shader;

        std::unique_ptr<Texture> _sample_texture_1;
        std::unique_ptr<Texture> _sample_texture_2;
    };
}