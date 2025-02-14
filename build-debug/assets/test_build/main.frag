#version 330 core

out vec4 fragment_color;
in vec2 output_positions;
// in vec3 output_color;

uniform float u_time;
// uniform float lerp_value;

void main() {
  // vec3 gradient = vec3(lerp_value, 0.0, lerp_value);
  vec2 modifier = vec2(abs(sin(u_time)));
  // modifier = clamp(modifier, vec2(0.0), vec2(5.0));
  fragment_color = vec4(output_positions.xy * (modifier + 4.0), 0.0, 1.0);
}