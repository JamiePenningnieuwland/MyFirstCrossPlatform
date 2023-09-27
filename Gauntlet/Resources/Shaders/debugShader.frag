#version 310 es
precision mediump float;

uniform vec3 uColor;
uniform vec3 uLightDir;

in vec3 color;

out vec4 FragColor;

void main()
{
	
	FragColor = vec4(color, 1.);
}