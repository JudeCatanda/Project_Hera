#version 330 core

in vec2 out_texture_position;
out vec4 Frag_Color;

uniform sampler2D textures_sample_data;

void main() {
  Frag_Color = texture(textures_sample_data, out_texture_position);
}