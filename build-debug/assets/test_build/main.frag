#version 330 core

out vec4 fragment_color;
uniform float lerp_value;
uniform float u_time;

void main() {
  vec3 gradient = vec3(lerp_value, 0.0, 0.0);
  fragment_color = vec4(gradient, 1.0);
}