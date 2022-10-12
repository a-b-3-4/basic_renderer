#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

void main()
{
   gl_Position =  u_view_projection * u_transform * position;
}