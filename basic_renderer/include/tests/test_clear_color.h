#pragma once

#include "tests/test.h"

namespace test
{
    class Test_clear_color : public Test
    {
    public:
        Test_clear_color();
        ~Test_clear_color();

        void on_update(float delta_time) override;
        void on_render() override;
        void on_ImGui_render() override;
    private:
        float _clear_color[4];
    };
}