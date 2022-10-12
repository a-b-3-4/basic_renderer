#include <imgui/imgui.h>

#include "tests/test.h"

namespace test
{
    Test_menu::Test_menu(Test*& current_test_pointer)
    : _current_test(current_test_pointer)
    {

    }
    void Test_menu::on_ImGui_render()
    {
        for(auto& test : _tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                _current_test = test.second();
            }
        }
    }
}