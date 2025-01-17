#version 330 core

layout (location = 0) in vec2 input_positions;
uniform float lerp_value;

void main() {
  gl_Position = vec4(input_positions * lerp_value, 0.0, 1.0); //wow!
}