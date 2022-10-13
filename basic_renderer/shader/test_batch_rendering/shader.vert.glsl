#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texture_coordinate;
layout(location = 3) in float a_texture_index;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

out vec4 v_color;
out vec2 v_texture_coordinate;
out float v_texture_index;

void main()
{
   v_color = a_color;
   v_texture_coordinate = a_texture_coordinate;
   v_texture_index = a_texture_index;
   
   gl_Position = u_view_projection * u_transform *  vec4(a_position, 1.0);
}