#include <gl/glew.h>
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

#include "tests/test_pong.h"
#include "renderer.h"

namespace test
{
    Test_pong::Test_pong()
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
    
    Test_pong::~Test_pong()
    {
        Renderer::shutdown();
    }
    

    void Test_pong::on_update(float delta_time)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 projection(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f));
        glm::mat4 view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
        glm::mat4 view_projection = projection * view;

        _shader->bind();
        _shader->set_uniform_matrix_4f("u_view_projection", view_projection);
        _shader->set_uniform_matrix_4f("u_transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

        Renderer::reset_statistics();
        Renderer::begin_batch();

        Renderer::draw_quad({ 0.0f, 220.0f }, { 10.0f, 100.0f }, _sample_texture_1.get());
        Renderer::draw_quad({ 950.0f, 220.0f }, { 10.0f, 100.0f }, _sample_texture_1.get());
        Renderer::draw_quad({ 475.0f, 265.0f }, { 10.0f, 10.0f }, _sample_texture_1.get());

        Renderer::end_batch();

        Renderer::flush();
    }

    void Test_pong::on_render()
    {

    }

    
    void Test_pong::on_ImGui_render()
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Quads: %d", Renderer::get_statistics().quad_count);
        ImGui::Text("draws: %d", Renderer::get_statistics().draw_count);
    }
}