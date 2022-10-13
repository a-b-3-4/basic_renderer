#include <gl/glew.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tests/test_batch_rendering.h"
#include "renderer.h"

namespace test
{
    Test_batch_rendering::Test_batch_rendering()
    {
        _shader = std::make_unique<Shader>("../basic_renderer/shader/test_batch_rendering/shader.vert.glsl", "../basic_renderer/shader/test_batch_rendering/shader.frag.glsl");

        int samplers[2] = { 0, 1 };
        _shader->bind();
        _shader->set_uniform_1iv("u_textures", 2, samplers);

        float positions[] = 
        {
            -1.5f, -0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -1.5f,  0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
 
             0.5f, -0.5f, 0.0f,  0.35f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             1.5f, -0.5f, 0.0f,  0.35f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             1.5f,  0.5f, 0.0f,  0.35f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, 0.0f,  0.35f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };
        _vertex_array = std::make_unique<Vertex_array>();
        
        _vertex_buffer = std::make_unique<Vertex_buffer>(positions, sizeof(positions));

        Vertex_buffer_layout vertex_buffer_layout;
        vertex_buffer_layout.push<float>(3); //position
        vertex_buffer_layout.push<float>(4); //color
        vertex_buffer_layout.push<float>(2); //texture coordiante
        vertex_buffer_layout.push<float>(1); //texture index
        _vertex_array->add_buffer(*_vertex_buffer, vertex_buffer_layout);
 
        unsigned int indecies[] =
        {
            0, 1, 2,
            2, 3, 0,
            
            4, 5, 6,
            6, 7, 4
        };
        _index_buffer = std::make_unique<Index_buffer>(indecies, sizeof(indecies)/sizeof(unsigned int));

        _texture_a = std::make_unique<Texture>("../basic_renderer/res/textures/sample_texture_1.png");
        _texture_b = std::make_unique<Texture>("../basic_renderer/res/textures/sample_texture_2.png");
        _texture_a->bind(0);
        _texture_b->bind(1);
    }
    
    Test_batch_rendering::~Test_batch_rendering()
    {

    }
    

    void Test_batch_rendering::on_update(float delta_time)
    {

    }

    void Test_batch_rendering::on_render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer renderer;
        
        glm::mat4 projection(glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, -1.0f, 1.0f));
        glm::mat4 view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
        glm::mat4 view_projection = projection * view;

        _shader->bind();
        _shader->set_uniform_matrix_4f("u_view_projection", view_projection);
        _shader->set_uniform_matrix_4f("u_transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

        renderer.draw(*_vertex_array, *_index_buffer, *_shader);
    }
    
    void Test_batch_rendering::on_ImGui_render()
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}