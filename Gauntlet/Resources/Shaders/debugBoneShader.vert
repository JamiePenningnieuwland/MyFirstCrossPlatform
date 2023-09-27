#version 310 es
//basic rule
//- highp for vertex positions,
//- mediump for texture coordinates,
//- lowp for colors.
//precision mediump float;
precision highp float;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 Model;

vec3 point[2] = vec3[] (
    vec3(0, 0, 0), vec3(0,  12., 0)
);

void main()
{
    vec3 p = point[gl_VertexID].xyz;
    gl_Position = (projection * inverse(view) * Model) * vec4(p, 1.);
};