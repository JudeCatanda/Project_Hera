#version 330 core

layout (location = 0) in vec2 input_positions;
uniform float lerp_value;
uniform float u_time;

out vec2 output_positions;

void main() {
  gl_Position = vec4(input_positions, 0.0, 1.0);
  output_positions = input_positions;
}