#include <gl/glew.h>
#include <imgui/imgui.h>

#include "tests/test_clear_color.h"

namespace test
{
    Test_clear_color::Test_clear_color()
    : _clear_color{ 0.5f, 0.0f, 1.0f, 1.0f }
    {

    }
    
    Test_clear_color::~Test_clear_color()
    {

    }
    

    void Test_clear_color::on_update(float delta_time)
    {

    }

    void Test_clear_color::on_render()
    {
        glClearColor(_clear_color[0], _clear_color[1], _clear_color[2], _clear_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void Test_clear_color::on_ImGui_render()
    {
        ImGui::ColorEdit4("clear color", _clear_color);
    }
}