#version 330 core

layout (location = 0) in vec2 local_mesh_postions;
layout (location = 1) in vec3 offset_positions;

uniform mat4 projection;
uniform mat4 view;

void main() {
  vec4 new_pos = vec4(offset_positions, 1.0);
  mat4 model = mat4(new_pos, new_pos, new_pos, new_pos);
  gl_Position = projection * view * model * vec4(local_mesh_postions + offset_positions.xy, 0.0, 1.0);
};