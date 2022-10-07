#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/glew.h>
#include <iostream>
#include <loga/log.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "shader.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "renderer.h"
#include "texture.h"

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        FATAL << "glfw didn't initionalize";
        return -1;
    }
    window = glfwCreateWindow(960, 540, "basic renderer", NULL, NULL);
    if (!window)
    {
        FATAL << "glfw failed to create a window";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if(glewInit() != GLEW_OK)
    {
        WARNING << "glew didn't initionalize";
    }
    INFO << "OpenGL version: " << glGetString(GL_VERSION);
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

        Vertex_array vertex_array;
        Vertex_buffer vertex_buffer(positions, 4 * 4 * sizeof(float));

        Vertex_buffer_layout vertex_buffer_layout;
        vertex_buffer_layout.push<float>(2); //positions
        vertex_buffer_layout.push<float>(2); //texture coordiantes
        vertex_array.add_buffer(vertex_buffer, vertex_buffer_layout);

        Index_buffer index_buffer(indecies, 6);

        glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader shader("../basic_renderer/shader/shader.vert", "../basic_renderer/shader/shader.frag");
        shader.bind();

        Texture texture("../basic_renderer/res/textures/florian.png");
        texture.bind();
        shader.set_uniform_1i("u_texture", 0);

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translation_a(150, 150, 0);
        glm::vec3 translation_b(450, 450, 0);

        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplGlfwGL3_NewFrame();

            renderer.clear();
            {
                glm::mat4 view = glm::translate(glm::mat4(1.0f), translation_a);
                glm::mat4 mvp = projection * view * model;

                shader.bind();
                shader.set_uniform_matrix_4f("u_MVP", mvp);

                renderer.draw(vertex_array, index_buffer, shader);
            }

            {
                glm::mat4 view = glm::translate(glm::mat4(1.0f), translation_b);
                glm::mat4 mvp = projection * view * model;

                shader.bind();
                shader.set_uniform_matrix_4f("u_MVP", mvp);
                
                renderer.draw(vertex_array, index_buffer, shader);
            }

            {
                ImGui::SliderFloat3("translation a", &translation_a.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("translation b", &translation_b.x, 0.0f, 960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}