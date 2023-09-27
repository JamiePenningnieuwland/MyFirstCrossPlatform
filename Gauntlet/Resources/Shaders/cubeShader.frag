#version 310 es
precision mediump float;

uniform samplerCube Skybox;

in vec3 TexCoords;

out vec4 FragColor;

void main()
{    
    FragColor = texture(Skybox, TexCoords);
}