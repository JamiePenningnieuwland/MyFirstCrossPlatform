#pragma once
#include "gl.h"
#include "Texture.h"
#include "Engine/Rendering/Shaders/Shader.h"

#include <vector>
#include <glm/glm.hpp>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
	glm::vec3 tangent;
	glm::vec3 biTangent;
};
struct AnimatedVertex
{
	void SetVertexBoneToDefaultValue() 
	{
		for(int i = 0; i < 4; i++)
		{
			BoneID[i] = -1;
			boneWeights[i] = 0.f;
		}
	}
	void SetVertexBoneData(int Id, float weight)
	{
		for (int i = 0; i < 4; i++)
		{
			if(BoneID[i] < 0 && weight > 0.f )
			{
				BoneID[i] = Id;
				boneWeights[i] = weight;
				break;
			}
		}
	}
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
	glm::vec3 tangent;
	glm::vec3 biTangent;
	glm::ivec4 BoneID;
	glm::vec4 boneWeights;
};

class Mesh
{

public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	Mesh(std::vector<AnimatedVertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	void Draw(Shader& shader);
	void DrawLines();
	std::vector<Texture>& GetTextures() 
	{
		return m_Textures;
	}
	void AddTextures(Texture t)
	{
		m_Textures.push_back(t);
	}
private:
	//VAO acts like id on gpu

	std::vector<Texture> m_Textures;
	GLuint m_ID = 0;
	std::vector<GLuint> m_VBOs;
	GLuint m_IBO;
	size_t m_NumIndex;
};
