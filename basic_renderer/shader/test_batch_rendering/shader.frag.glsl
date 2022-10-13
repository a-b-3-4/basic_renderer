#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_texture_coordinate;
in float v_texture_index;

uniform sampler2D u_textures[2];

void main()
{
   int texture_index = int(v_texture_index);
   color = texture(u_textures[texture_index], v_texture_coordinate);
}