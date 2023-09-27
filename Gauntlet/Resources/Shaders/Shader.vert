#version 310 es
//basic rule
//- highp for vertex positions,
//- mediump for texture coordinates,
//- lowp for colors.
//precision mediump float;
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBiTangent;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 Model;

out mat3 TBN;
out vec2 UV;

void main()
{
	//normals need to be transformed to worldspace
	vec3 normal = normalize(aNormal * inverse(mat3(Model)));
	vec3 tangent = normalize(aTangent * inverse(mat3(Model)));
	vec3 biTangent = normalize(aBiTangent * inverse(mat3(Model)));
	TBN = mat3(tangent, biTangent, normal);

	UV = aUV;
    gl_Position = projection * inverse(view) * Model * vec4(aPos, 1.0);
}