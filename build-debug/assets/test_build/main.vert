#version 330 core

layout (location = 0) in vec2 input_positions;
layout (location = 1) in vec3 input_color;

uniform float lerp_value;
uniform float u_time;

out vec2 output_positions;
out vec3 output_color;

void main() {
  gl_Position = vec4(input_positions, 0.0, 1.0);
  output_positions = input_positions;
  output_color = input_color;
}