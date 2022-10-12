#pragma once

#include <functional>
#include <vector>

#include "loga/log.h"

namespace test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void on_update(float delta_time) {}
        virtual void on_render() {}
        virtual void on_ImGui_render() {}
    };

    class Test_menu : public Test
    {
    public:
        Test_menu(Test*& current_test_pointer);

        void on_ImGui_render() override;

        template<typename T>
        void register_test(const std::string& name)
        {
            INFO << "registering test \"" << name << "\"";

            _tests.push_back(std::make_pair(name, []() {return new T(); }));
        }
    private:
        Test*& _current_test;
        std::vector<std::pair<std::string, std::function<Test*()>>> _tests;
    };
}