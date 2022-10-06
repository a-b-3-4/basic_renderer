#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/glew.h>
#include <iostream>

#include "shader_generation.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "log.h"

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
        -0.5f, -1.0f,
         0.5f, -0.5f,
         0.5f,  1.0f,
        -0.5f,  0.5f
    };
    unsigned int indecies[6] =
    {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Vertex_buffer vertex_buffer(positions, 2*4*sizeof(float));

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    Index_buffer index_buffer(indecies, 6);

    unsigned int shader = create_shader("../basic_renderer/shader/shader.vert", "../basic_renderer/shader/shader.frag");
    glUseProgram(shader);

    int u_color = glGetUniformLocation(shader, "u_color");
    if(u_color == -1)
    {
        WARNING << "uniform \"u_color\" not used!";
    }

    float r = 1.0f;
    float increment = 0.01f;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shader);
        glUniform4f(u_color, r, 0.0f, 1.0f, 1.0f);
        glBindVertexArray(vao);
        index_buffer.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        if(r > 1.0f)
            increment = -0.01f;
        else if(r < 0.5f)
            increment = 0.01f;
        r += increment;


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    index_buffer.~Index_buffer();
    vertex_buffer.~Vertex_buffer();
    glfwTerminate();
    return 0;
}