#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texture_position;

out vec2 out_texture_position;
uniform mat4 projection;
uniform vec2 new_pos;


void main() {
  gl_Position = projection * vec4(pos + new_pos, 0.0, 1.0);
  out_texture_position = texture_position;
};