#version 310 es
//basic rule
//- highp for vertex positions,
//- mediump for texture coordinates,
//- lowp for colors.
//precision mediump float;
precision highp float;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 Model;

uniform vec3 uPosition[2];
uniform vec3 uColor;

out vec3 color;

void main()
{
    color = uColor;
    gl_Position = projection * inverse(view) * vec4(uPosition[gl_VertexID], 1.0);
}