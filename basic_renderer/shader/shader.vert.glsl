#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texture_coordinate;

out vec2 v_texture_coordinate;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_texture_coordinate = texture_coordinate;
}