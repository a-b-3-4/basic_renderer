#include "shader_generation.h"
#include <gl/glew.h>
#include <iostream>
#include <fstream>
#include <string>

std::string parse_shader(const std::string& shader_filepath)
{
    std::ifstream stream(shader_filepath);
    std::string shader((std::istreambuf_iterator<char>(stream)),
                       (std::istreambuf_iterator<char>()));
    return shader;
}

unsigned int compile_shader(unsigned int type, const std::string& source)
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
        //TODO: change to log (start)
        std::cout << "ERROR: failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:\n" << message << "\n";
        //TODO: change to log (end)
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int create_shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
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