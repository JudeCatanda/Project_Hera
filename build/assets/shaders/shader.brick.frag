#version 330 core

out vec4 fragColor;
in vec2 outTexPOS;

uniform sampler2D texturesampler;

void main() {
  fragColor = texture(texturesampler, outTexPOS);
}