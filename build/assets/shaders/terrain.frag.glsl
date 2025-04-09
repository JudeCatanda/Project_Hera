#version 330 core

uniform sampler2D tex1;
in vec2 out_ins_tex_pos;
out vec4 frag;

void main() {
  frag = texture(tex1, out_ins_tex_pos);
}
