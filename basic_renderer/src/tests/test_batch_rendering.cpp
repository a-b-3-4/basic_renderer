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

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        float positions[] = 
        {
            -1.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            -1.5f,  0.5f, 0.0f,

             0.5f, -0.5f, 0.0f,
             1.5f, -0.5f, 0.0f,
             1.5f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f
        };
        _vertex_array = std::make_unique<Vertex_array>();
        
        _vertex_buffer = std::make_unique<Vertex_buffer>(positions, sizeof(positions));

        Vertex_buffer_layout vertex_buffer_layout;
        vertex_buffer_layout.push<float>(3); //positions
        _vertex_array->add_buffer(*_vertex_buffer, vertex_buffer_layout);
 
        unsigned int indecies[] =
        {
            0, 1, 2,
            2, 3, 0,
            
            4, 5, 6,
            6, 7, 4
        };
        _index_buffer = std::make_unique<Index_buffer>(indecies, sizeof(indecies)/sizeof(unsigned int));
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