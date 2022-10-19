#include <gl/glew.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tests/test_textures_2d.h"
#include "renderer.h"

namespace test
{
    Test_textures_2d::Test_textures_2d()
    : _projection(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
      _view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
      _translation_a(150, 150, 0), _translation_b(450, 450, 0)
    {
        float positions[] = 
        {
            -150.0f,  150.0f, 0.0f, 1.0f,
             150.0f,  150.0f, 1.0f, 1.0f,
            -150.0f, -150.0f, 0.0f, 0.0f,
             150.0f, -150.0f, 1.0f, 0.0f
        };
        unsigned int indecies[6] =
        {
            0, 1, 2,
            1, 2, 3
        };
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        _vertex_array = std::make_unique<Vertex_array>();

        _vertex_buffer = std::make_unique<Vertex_buffer>(positions, 4 * 4 * sizeof(float));
        Vertex_buffer_layout vertex_buffer_layout;
        vertex_buffer_layout.push<float>(2); //positions
        vertex_buffer_layout.push<float>(2); //texture coordiantes
        _vertex_array->add_buffer(*_vertex_buffer, vertex_buffer_layout);
 
        _index_buffer = std::make_unique<Index_buffer>(indecies, 6);

        _shader = std::make_unique<Shader>("../basic_renderer/shader/shader.vert.glsl", "../basic_renderer/shader/shader.frag.glsl");
        _shader->bind();

        _texture = std::make_unique<Texture>("../basic_renderer/resources/textures/sample_texture_3.png");
        _shader->set_uniform_1i("u_texture", 0);
    }
    
    Test_textures_2d::~Test_textures_2d()
    {

    }
    

    void Test_textures_2d::on_update(float delta_time)
    {

    }

    void Test_textures_2d::on_render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer renderer;

        _texture->bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), _translation_a);
            glm::mat4 mvp = _projection * _view * model;
            _shader->bind();
            _shader->set_uniform_matrix_4f("u_MVP", mvp);
            renderer.draw(*_vertex_array, *_index_buffer, *_shader, 6);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), _translation_b);
            glm::mat4 mvp = _projection * _view * model;
            _shader->bind();
            _shader->set_uniform_matrix_4f("u_MVP", mvp);
            renderer.draw(*_vertex_array, *_index_buffer, *_shader, 6);
        }
    }
    
    void Test_textures_2d::on_ImGui_render()
    {
            ImGui::SliderFloat3("translation a", &_translation_a.x, 0.0f, 960.0f);
            ImGui::SliderFloat3("translation b", &_translation_b.x, 0.0f, 960.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}