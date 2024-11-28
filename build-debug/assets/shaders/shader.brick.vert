#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 2) in vec2 TexPOS;
layout (location = 1) in vec2 spos;

out vec2 outTexPOS;

uniform mat4 projection;

void main()
{
  gl_Position = projection * vec4(pos + spos, 1.0, 1.0);
  outTexPOS = TexPOS;
}