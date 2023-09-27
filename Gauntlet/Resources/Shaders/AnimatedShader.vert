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

layout (location = 5) in ivec4 aBoneIDs;
layout (location = 6) in vec4 aWeights;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 Model;

const int MAX_BONES = 100;

uniform mat4 BoneMatrices[MAX_BONES];

//out mat3 TBN;
out vec2 UV;

out vec3 normal;
out vec3 tangent;
out vec3 biTangent;

void main()
{
	vec4 totalPosition = vec4(0.);
	vec3 totalNormal = vec3(0.);
	vec3 totalTangent = vec3(0.);
	vec3 totalBiTangent = vec3(0.);

	bool noBones = true;
	for(int i = 0; i < 4; i++)
	{
		if(aBoneIDs[i] == -1)
			continue;

		noBones = false;

		if(aBoneIDs[i] > MAX_BONES)
		{
			noBones = true;
			break;
		}
		vec4 localPosition = BoneMatrices[aBoneIDs[i]] * vec4(aPos, 1.);
		totalPosition += localPosition * aWeights[i];

		vec3 localNormal = mat3(BoneMatrices[aBoneIDs[i]]) * aNormal;
		totalNormal += localNormal * aWeights[i];

		vec3 localTangent = mat3(BoneMatrices[aBoneIDs[i]]) * aTangent;
		totalTangent += localTangent * aWeights[i];

		vec3 localBiTangent = mat3(BoneMatrices[aBoneIDs[i]]) * aBiTangent;
		totalBiTangent += localBiTangent * aWeights[i];
	}
	if(noBones == true)
	{
		totalPosition = vec4(aPos, 1.);
		totalNormal = aNormal;
		totalTangent = aTangent;
		totalBiTangent = aBiTangent;
	}
	normal = normalize(totalNormal * inverse(mat3(Model)));
	tangent = normalize(totalTangent * inverse(mat3(Model)));
	biTangent = normalize(totalBiTangent * inverse(mat3(Model)));

	UV = aUV;
    gl_Position = projection * inverse(view) * Model * totalPosition;
}