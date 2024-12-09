#version 330 core

layout (location = 0) in vec4 vertex; // (position.xy, texCoords.xy)

out vec2 TexCoords; // Pass texture coordinates to the fragment shader

uniform mat4 projection; // Projection matrix to handle screen scaling

void main() {
    // Set the vertex position
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    
    // Pass the texture coordinates
    TexCoords = vertex.zw;
}
