#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/glew.h>
#include <iostream>
#include <loga/log.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    window = glfwCreateWindow(640, 480, "basic renderer", NULL, NULL);
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
            -0.5f,  0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f
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

        glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

        Shader shader("../basic_renderer/shader/shader.vert", "../basic_renderer/shader/shader.frag");
        shader.bind();
        shader.set_uniform_matrix_4f("u_MVP", projection);

        Texture texture("../basic_renderer/res/textures/florian.png");
        texture.bind();
        shader.set_uniform_1i("u_texture", 0);

        Renderer renderer;
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();
            renderer.draw(vertex_array, index_buffer, shader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}