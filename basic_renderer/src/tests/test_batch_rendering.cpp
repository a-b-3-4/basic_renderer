#include <gl/glew.h>
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

#include "tests/test_batch_rendering.h"
#include "renderer.h"

namespace test
{
    Test_batch_rendering::Test_batch_rendering()
    {
        _shader = std::make_unique<Shader>("../basic_renderer/shader/test_batch_rendering/shader.vert", "../basic_renderer/shader/test_batch_rendering/shader.frag");

        int samplers[32];
        for(int i = 0; i < 32; i++)
        {
            samplers[i] = i;
        }
        _shader->bind();
        _shader->set_uniform_1iv("u_textures", 32, samplers);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        Renderer::init();
        
        _sample_texture_1 = std::make_unique<Texture>("../basic_renderer/resources/textures/sample_texture_1.png");
        _sample_texture_2 = std::make_unique<Texture>("../basic_renderer/resources/textures/sample_texture_2.png");
    }
    
    Test_batch_rendering::~Test_batch_rendering()
    {
        Renderer::shutdown();
    }
    

    void Test_batch_rendering::on_update(float delta_time)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 projection(glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, -1.0f, 1.0f));
        glm::mat4 view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
        glm::mat4 view_projection = projection * view;

        _shader->bind();
        _shader->set_uniform_matrix_4f("u_view_projection", view_projection);
        _shader->set_uniform_matrix_4f("u_transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

        Renderer::reset_statistics();
        Renderer::begin_batch();

        for(float y = -10.0f; y < 10.0f; y += 0.25f)
        {
            for(float x = -10.0f; x < 10.0f; x += 0.25f)
            {
                glm::vec4 color =
                {
                    (x + 10) / 20.0f, 
                    0.2f,
                    (y + 10) / 20.0f,
                    1.0f
                };
                Renderer::draw_quad({ x, y }, { 0.20f, 0.20f }, color);
            }
        }
        for(int y = 0; y < 10; y++)
        {
            for(int x = 0; x < 10; x++)
            {
                Renderer::draw_quad({ x, y }, { 1.0f, 1.0f }, ((x + y) % 2 == 0) ? _sample_texture_1.get() : _sample_texture_2.get());
            }
        }
        Renderer::draw_quad(_quad_position, { 1.0f, 1.0f }, _sample_texture_1.get());

        Renderer::end_batch();

        Renderer::flush();
    }

    void Test_batch_rendering::on_render()
    {

    }

    
    void Test_batch_rendering::on_ImGui_render()
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Quads: %d", Renderer::get_statistics().quad_count);
        ImGui::Text("draws: %d", Renderer::get_statistics().draw_count);
        ImGui::DragFloat2("quad position", glm::value_ptr(_quad_position), 0.1f);
    }
}