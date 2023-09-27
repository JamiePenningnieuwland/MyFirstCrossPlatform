#pragma once
#include <string>
#include <vector>
#include "Animation.h"
#include "Mesh.h"
#include <assimp/material.h>

struct aiNode;
struct aiScene;
struct aiMesh;
class Mesh;

class Model
{
public:
	Model() : m_Meshes() {};
	Model(std::string fileName /*std::string mapName, glm::vec3 scale = glm::vec3(1.f)*/);
	Model(std::vector<Mesh> mesh, std::string t/*, std::string mapname*/);

	void Draw(Shader& shader);
	void DrawLines();
	bool Animated = false;

	//std::string GetName() { return m_Name; }
	SkeletalMesh& GetSkeleton() { return skeleton; }
	SkeletalMesh CopySkeleton() { return skeleton; }
	std::string GetFullDirectory()
	{
		return FullDirectory;
	}
	bool GeneratedMesh = false;
private:
	std::vector<Mesh> m_Meshes;
	std::string directory;
	std::string FullDirectory;
	//std::string m_Name;
	SkeletalMesh skeleton;
	//std::map<std::string, Animation> m_Animations;

	void ProcessNode(int parent, aiNode* node);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName,const aiScene* );
};