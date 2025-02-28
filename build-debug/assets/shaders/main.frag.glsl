#version 330 core

out vec4 FragColor;
in vec2 o_tex_coord;
uniform sampler2D asset;

void main() {
  // FragColor = vec4(0.0, 1.0, 0.0, 1.0);
  FragColor = texture(asset, o_tex_coord);
};