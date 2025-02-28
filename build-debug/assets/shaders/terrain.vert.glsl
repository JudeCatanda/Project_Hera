#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 2) in vec2 offset_pos;

layout(std140) uniform Matrices {
  mat4 p;
  mat4 v;
};

void main() {
  mat4 cam = p * v;
  gl_Position = cam * vec4(aPos + offset_pos, 0.0, 1.0);
};