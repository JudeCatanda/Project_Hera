#version 330 core

layout (location = 0) in vec2 input_positions;
uniform float lerp_value;
uniform float u_time;

void main() {
  gl_Position = vec4(input_positions/*sin(input_positions * u_time)*/, 0.0, 1.0);
}