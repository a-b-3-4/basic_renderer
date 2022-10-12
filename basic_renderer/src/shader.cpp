#include <gl/glew.h>
#include <iostream>
#include <fstream>
#include <string>

#include "shader.h"
#include "loga/log.h"

Shader::Shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
{
    _renderer_id = create_shader(vertex_shader_filepath, fragment_shader_filepath);
}

Shader::~Shader()
{
    glDeleteProgram(_renderer_id);
}


std::string Shader::parse_shader(const std::string& shader_filepath)
{
    std::ifstream stream(shader_filepath);
    std::string shader((std::istreambuf_iterator<char>(stream)),
                       (std::istreambuf_iterator<char>()));
    return shader;
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::string message_string = message;
        message_string.pop_back();
        ERROR << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:\n" << message_string;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::create_shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
{
    std::string vertex_shader = parse_shader(vertex_shader_filepath);
    std::string fragment_shader = parse_shader(fragment_shader_filepath);

    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::bind() const
{
    glUseProgram(_renderer_id);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

//set uniforms
void Shader::set_uniform_1i(const std::string& name, int value)
{
    glUniform1i(get_uniform_location(name), value);
}
void Shader::set_uniform_1f(const std::string& name, float value)
{
    glUniform1f(get_uniform_location(name), value);
}
void Shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}
void Shader::set_uniform_matrix_4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::get_uniform_location(const std::string& name)
{
    if(_uniform_location_cache.find(name) != _uniform_location_cache.end())
        return _uniform_location_cache[name];
    int location = glGetUniformLocation(_renderer_id, name.c_str());
    if(location == -1)
        WARNING << "uniform \"" << name << "\" doesn't exist!";
    _uniform_location_cache[name] = location;
    return location;
}