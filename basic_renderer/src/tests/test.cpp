#include <imgui/imgui.h>

#include "tests/test.h"

namespace test
{
    Test_menu::Test_menu(Test*& current_test_pointer)
    : m_current_test(current_test_pointer)
    {

    }
    void Test_menu::on_ImGui_render()
    {
        for(auto& test : m_tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                m_current_test = test.second();
            }
        }
    }
}