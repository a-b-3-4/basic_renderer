#pragma once

#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    //set uniforms
    void set_uniform_1i(const std::string& name, int value);
    void set_uniform_1f(const std::string& name, float value);
    void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);
    void set_uniform_matrix_4f(const std::string& name, const glm::mat4& matrix);
private:
    std::string parse_shader(const std::string& shader_filepath);
    unsigned int compile_shader(unsigned int type, const std::string& source);
    unsigned int create_shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);

    int get_uniform_location(const std::string& name) const;
private:
    unsigned int _renderer_id;
    mutable std::unordered_map<std::string, int> _uniform_location_cache;
};