#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/glew.h>
#include <iostream>

#include "log.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "basic renderer", NULL, NULL);
    if (!window)
    {
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
    float positions[] = 
    {
        -1.0f, -1.0f,
         0.5f, -0.5f,
         1.0f,  1.0f,
        -0.5f,  0.5f
    };
    unsigned int indecies[6] =
    {
        0, 1, 2,
        2, 3, 0
    };

    Vertex_array vertex_array;
    Vertex_buffer vertex_buffer(positions, 2*4*sizeof(float));

    Vertex_buffer_layout vertex_buffer_layout;
    vertex_buffer_layout.push<float>(2);
    vertex_array.add_buffer(vertex_buffer, vertex_buffer_layout);
    
    Index_buffer index_buffer(indecies, 6);

    Shader shader("../basic_renderer/shader/shader.vert", "../basic_renderer/shader/shader.frag");
    shader.bind();
    shader.set_uniform_4f("u_color", 0.5f, 0.0f, 1.0f, 1.0f);

    float r = 0.5f;
    float increment = 0.01f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        shader.bind();
        shader.set_uniform_4f("u_color", r, 0.0f, 1.0f, 1.0f);
        vertex_array.bind();
        index_buffer.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        if(r > 0.7f)
            increment = -0.01f;
        else if(r < 0.5f)
            increment = 0.01f;
        r += increment;


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shader.~Shader();
    index_buffer.~Index_buffer();
    vertex_buffer.~Vertex_buffer();
    glfwTerminate();
    return 0;
}