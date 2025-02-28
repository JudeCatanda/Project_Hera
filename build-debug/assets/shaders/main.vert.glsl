#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 2) in vec2 tex_coord;

layout(std140) uniform Matrices {
  mat4 projection;
  mat4 view;
};
uniform vec2 position;

out vec2 o_tex_coord;

void main() {
  gl_Position = projection * view * vec4(aPos + position, 0.0, 1.0);
  o_tex_coord = tex_coord;
};