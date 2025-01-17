#version 330 core

out vec4 fragment_color;
uniform float lerp_value;

void main() {
  vec3 gradient = mix(vec3(0.0, 0.0, lerp_value), vec3(lerp_value, 0.0, 0.0), 0.5);
  fragment_color = vec4(gradient, 1.0);
}