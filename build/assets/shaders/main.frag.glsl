#version 330 core

in vec2 out_tex_pos;
uniform sampler2D asset;
out vec4 frag;

void main() {
  frag = texture(asset, out_tex_pos);
}
