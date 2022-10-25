#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <loga/log.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "tests/test_clear_color.h"
#include "tests/test_batch_rendering.h"

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
        WARNING << "glew didn't initionalize";
    INFO << "OpenGL version: " << glGetString(GL_VERSION);

    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::Test* current_test = nullptr;
        test::Test_menu* test_menu = new test::Test_menu(current_test);
        current_test = test_menu;

        test_menu->register_test<test::Test_clear_color>("clear color");
        test_menu->register_test<test::Test_batch_rendering>("batch rendering");

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplGlfwGL3_NewFrame();

            if(current_test)
            {
                current_test->on_update(0.0f);
                current_test->on_render();
                ImGui::Begin("Test");
                if(current_test != test_menu && ImGui::Button("<-"))
                {
                    delete current_test;
                    current_test = test_menu;
                }
                current_test->on_ImGui_render();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        delete current_test;
        if(current_test != test_menu)
            delete test_menu;
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}