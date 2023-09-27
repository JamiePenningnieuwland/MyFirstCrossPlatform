#version 310 es
//basic rule
//- highp for vertex positions,
//- mediump for texture coordinates,
//- lowp for colors.
//precision mediump float;
precision highp float;

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 TexCoords;

void main()
{
    vec4 pos = projection * inverse(view) * vec4(aPos, 1.0f);
    gl_Position = pos.xyww;
    TexCoords = aPos;
} 