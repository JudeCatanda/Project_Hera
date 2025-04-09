#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 2) in vec2 tex_pos; //what?

uniform Matrices {
  mat4 projection;
  mat4 view;
};

uniform sampler2D asset; //what??
uniform vec2 position;
out vec2 out_tex_pos;

void main() {
  gl_Position = projection * view * vec4(pos + position, 0.0, 1.0);
  out_tex_pos = tex_pos;
}
