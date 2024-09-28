#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 spos;

void main()
{
  gl_Position = vec4(pos + spos, 1.0, 1.0);
}