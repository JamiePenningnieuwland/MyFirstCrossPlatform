#version 310 es
precision mediump float;


out vec4 FragColor;

void main()
{
    gl_FragDepth = 0.;
    FragColor = vec4(0.5, 0.5, 0.8, 1.);
}