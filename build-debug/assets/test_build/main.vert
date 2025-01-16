#version 330 core

layout (location = 0) in vec2 input_positions;

void main() {
  gl_Position = vec4(input_positions, 0.0, 1.0);
}