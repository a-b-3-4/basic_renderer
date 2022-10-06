#pragma once

#include <iostream>
#include <unordered_map>

class Shader
{
private:
    unsigned int m_renderer_id;
    std::unordered_map<std::string, int> m_uniform_location_cache;
public:
    Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    //set uniforms
    void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
    std::string parse_shader(const std::string& shader_filepath);
    unsigned int compile_shader(unsigned int type, const std::string& source);
    unsigned int create_shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
    int get_uniform_location(const std::string& name);
};