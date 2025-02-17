#version 330 core

layout (location = 0) in vec2 local_mesh_postions;
layout (location = 1) in vec2 offset_positions;

uniform mat4 projection;

void main() {
  gl_Position = projection * vec4(local_mesh_postions + offset_positions, 0.0, 1.0);
};