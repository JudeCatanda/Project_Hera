#version 330 core

in vec2 TexCoords; // Texture coordinates passed from the vertex shader
out vec4 color;    // Final fragment color

uniform sampler2D text;    // Glyph texture (monochrome)
uniform vec3 textColor;    // Text color

void main() {
    // Sample the texture at the given coordinates
    float alpha = texture(text, TexCoords).r; // Glyph is in the red channel

    // Set the fragment color, using the alpha from the texture and text color
    color = vec4(textColor, alpha);
}
