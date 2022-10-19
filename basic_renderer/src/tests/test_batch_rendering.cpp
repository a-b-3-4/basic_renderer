#include <gl/glew.h>
#include <imgui/imgui.h>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tests/test_batch_rendering.h"
#include "renderer.h"

namespace test
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texture_coordiante;
        float texture_id;
    };

    Test_batch_rendering::Test_batch_rendering()
    {
        _shader = std::make_unique<Shader>("../basic_renderer/shader/test_batch_rendering/shader.vert.glsl", "../basic_renderer/shader/test_batch_rendering/shader.frag.glsl");

        int samplers[2] = { 0, 1 };
        _shader->bind();
        _shader->set_uniform_1iv("u_textures", 2, samplers);

        const size_t maximum_quad_count = 1000;
        const size_t maximum_vertex_count = maximum_quad_count * 4;
        const size_t maximum_index_count = maximum_quad_count * 6;

        _vertex_array = std::make_unique<Vertex_array>();
        
        _vertex_buffer = std::make_unique<Vertex_buffer>(nullptr, maximum_vertex_count * sizeof(Vertex)); //TODO: change it to a constructor which just alocates space, and doesnt set values

        Vertex_buffer_layout vertex_buffer_layout;
        vertex_buffer_layout.push<float>(3); //position
        vertex_buffer_layout.push<float>(4); //color
        vertex_buffer_layout.push<float>(2); //texture coordiante
        vertex_buffer_layout.push<float>(1); //texture id
        _vertex_array->add_buffer(*_vertex_buffer, vertex_buffer_layout);

        //autogenerate indecies 
        uint32_t indecies[maximum_index_count];
        uint32_t offset = 0;
        for(size_t i = 0; i < maximum_index_count; i += 6)
        {
            indecies[i + 0] = 0 + offset;
            indecies[i + 1] = 1 + offset;
            indecies[i + 2] = 2 + offset;

            indecies[i + 3] = 2 + offset;
            indecies[i + 4] = 3 + offset;
            indecies[i + 5] = 0 + offset;
            offset += 4;
        }

        _index_buffer = std::make_unique<Index_buffer>(indecies, sizeof(indecies)/sizeof(unsigned int));

        _texture_a = std::make_unique<Texture>("../basic_renderer/resources/textures/sample_texture_1.png");
        _texture_b = std::make_unique<Texture>("../basic_renderer/resources/textures/sample_texture_2.png");
        _texture_a->bind(0);
        _texture_b->bind(1);
    }
    
    Test_batch_rendering::~Test_batch_rendering()
    {

    }
    

    void Test_batch_rendering::on_update(float delta_time)
    {

    }

    static Vertex* create_quad(Vertex* target, float x, float y, float size, float texture_id)
    {
        target->position = { x - size/2, y - size/2, 0.0f };
        target->color = { 0.5f, 0.0f, 1.0f, 1.0f };
        target->texture_coordiante = { 0.0f, 0.0f };
        target->texture_id = texture_id;
        target++;

        target->position = { x + size/2, y - size/2, 0.0f };
        target->color = { 0.5f, 0.0f, 1.0f, 1.0f };
        target->texture_coordiante = { 1.0f, 0.0f };
        target->texture_id = texture_id;
        target++;

        target->position = { x + size/2, y + size/2, 0.0f };
        target->color = { 0.5f, 0.0f, 1.0f, 1.0f };
        target->texture_coordiante = { 1.0f, 1.0f };
        target->texture_id = texture_id;
        target++;

        target->position = { x - size/2, y + size/2, 0.0f };
        target->color = { 0.5f, 0.0f, 1.0f, 1.0f };
        target->texture_coordiante = { 0.0f, 1.0f };
        target->texture_id = texture_id;
        target++;

        return target;
    }

    void Test_batch_rendering::on_render()
    {
        uint32_t index_count = 0;

        std::array<Vertex, 1000> vertecies;
        Vertex* buffer = vertecies.data();
        for(int x = 0; x < 10; x++)
        {
            for(int y = 0; y < 10; y++)
            {
                buffer = create_quad(buffer, x, y, 1, (x + y) % 2);
                index_count += 6;
            }
        }
        buffer = create_quad(buffer, _quad_1_position[0], _quad_1_position[1], _size[0], 0.0f);
        index_count += 6;
        buffer = create_quad(buffer, _quad_2_position[0], _quad_2_position[1], _size[1], 1.0f);
        index_count += 6;

        _vertex_buffer->bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertecies.size() * sizeof(Vertex), vertecies.data());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer renderer;
        
        glm::mat4 projection(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f));
        glm::mat4 view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
        glm::mat4 view_projection = projection * view;

        _shader->bind();
        _shader->set_uniform_matrix_4f("u_view_projection", view_projection);
        _shader->set_uniform_matrix_4f("u_transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

        renderer.draw(*_vertex_array, *_index_buffer, *_shader, index_count);
    }

    
    void Test_batch_rendering::on_ImGui_render()
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::DragFloat2("quad 1 position", _quad_1_position, 0.1f);
        ImGui::DragFloat2("quad 2 position", _quad_2_position, 0.1f);
        ImGui::DragFloat2("size", _size, 0.1f);
    }
}