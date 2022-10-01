#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader_generation.h"
#include <gl/glew.h>
#include <iostream>

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
    if(glewInit() != GLEW_OK)
    {
        //TODO: change to log (start)
        std::cout << "ERROR: glew didn't initionalize\n";
        //TODO: change to log (end)
    }
    //TODO: change to log (start)
    std::cout << "INFO: OpenGL version: " << glGetString(GL_VERSION) << "\n";
    //TODO: change to log (end)
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

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_DYNAMIC_DRAW);

    unsigned int shader = create_shader("../basic_renderer/shader/shader.vert", "../basic_renderer/shader/shader.frag");
    glUseProgram(shader);

    int u_color = glGetUniformLocation(shader, "u_color");
    if(u_color == -1)
    {
        //TODO: change to log (start)
        std::cout << "Warning: uniform \"u_color\" not used!\n";
        //TODO: change to log (end)
    }
    glUniform4f(u_color, 0.3f, 0.0f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}