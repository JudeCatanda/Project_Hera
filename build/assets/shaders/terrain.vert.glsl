#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 2) in vec2 ins_pos;
layout (location = 5) in vec2 ins_tex_pos;

out vec2 out_ins_tex_pos;

uniform Matrices {
  mat4 projection;
  mat4 view;
};

void main() {
  //+ins_pos
  gl_Position = projection * view * vec4(pos, 0.0, 1.0);
  out_ins_tex_pos = ins_tex_pos;
}
