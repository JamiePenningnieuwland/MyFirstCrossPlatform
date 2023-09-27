#include "Model.h"

#include <glm/gtx/matrix_decompose.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

//from assimp to glm found on learnopengl animation tutorial
glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
{
	glm::mat4 to;
	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
	to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
	to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
	to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
	return to;
}
glm::vec3 ConvertVec3ToGLMFormat(const aiVector3D& from)
{
	return glm::vec3(from.x, from.y, from.z);
}
glm::quat ConvertQuatToGLMFormat(const aiQuaternion& from)
{
	return glm::quat(from.w, from.x, from.y, from.z);
}
//----------------------------------------------------------

Model::Model(std::string fileName) 
	: m_Meshes()
	
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate |aiProcess_FlipUVs| aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
	Animated = scene->mAnimations != nullptr;
	FullDirectory = fileName;
	directory = fileName.substr(0, fileName.find_last_of("/"));
	//All vertex data
	if (!Animated)
	{
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;
			std::vector<Texture> textures;

			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				Vertex v;
				v.position.x = mesh->mVertices[j].x;
				v.position.y = mesh->mVertices[j].y;
				v.position.z = mesh->mVertices[j].z;

				if (mesh->HasNormals())
				{
					v.normal.x = mesh->mNormals[j].x;
					v.normal.y = mesh->mNormals[j].y;
					v.normal.z = mesh->mNormals[j].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					v.UV.x = mesh->mTextureCoords[0][j].x;
					v.UV.y = mesh->mTextureCoords[0][j].y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					v.tangent.x = mesh->mTangents[j].x;
					v.tangent.y = mesh->mTangents[j].y;
					v.tangent.z = mesh->mTangents[j].z;
					v.biTangent.x = mesh->mBitangents[j].x;
					v.biTangent.y = mesh->mBitangents[j].y;
					v.biTangent.z = mesh->mBitangents[j].z;

				}

				vertices.push_back(v);
			}
			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				aiFace face = mesh->mFaces[j];
				for (unsigned int k = 0; k < face.mNumIndices; k++)
				{
					indices.push_back(face.mIndices[k]);
				}
			}
			if(mesh->mMaterialIndex >= 0)
			{
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", scene);
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

				std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal", scene);
				textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			}
			m_Meshes.push_back(Mesh(vertices, indices, textures));

		}
	}
	//animation data
	else
	{
		std::vector<std::vector<AnimatedVertex>> vertices(scene->mNumMeshes);
		std::vector<std::vector<GLuint>> indices(scene->mNumMeshes);
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				AnimatedVertex v;

				v.position.x = mesh->mVertices[j].x;
				v.position.y = mesh->mVertices[j].y;
				v.position.z = mesh->mVertices[j].z;

				if (mesh->HasNormals())
				{
					v.normal.x = mesh->mNormals[j].x;
					v.normal.y = mesh->mNormals[j].y;
					v.normal.z = mesh->mNormals[j].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					v.UV.x = mesh->mTextureCoords[0][j].x;
					v.UV.y = mesh->mTextureCoords[0][j].y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					v.tangent.x = mesh->mTangents[j].x;
					v.tangent.y = mesh->mTangents[j].y;
					v.tangent.z = mesh->mTangents[j].z;
					v.biTangent.x = mesh->mBitangents[j].x;
					v.biTangent.y = mesh->mBitangents[j].y;
					v.biTangent.z = mesh->mBitangents[j].z;

				}
				v.SetVertexBoneToDefaultValue();
				vertices[i].push_back(v);
			}
			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				aiFace face = mesh->mFaces[j];
				for (unsigned int k = 0; k < face.mNumIndices; k++)
				{
					indices[i].push_back(face.mIndices[k]);
				}
			}

			if (mesh->mMaterialIndex >= 0)
			{
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", scene);
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

				std::vector<Texture> normalMaps = LoadMaterialTextures(material,aiTextureType_NORMALS, "texture_normal", scene);
				textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

			}
		}
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			if (mesh->HasBones())
			{
				for (unsigned int j = 0; j < mesh->mNumBones; j++)
				{
					skeleton.boneInfoMap[mesh->mBones[j]->mName.C_Str()] = 0;
				}
			}
		}

		ProcessNode(-1, scene->mRootNode);
		//attach vertices to bones
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			if (mesh->HasBones())
			{
				for (unsigned int j = 0; j < mesh->mNumBones; j++)
				{
					aiBone* bone = mesh->mBones[j];
					std::string boneName = bone->mName.C_Str();
					int ID = skeleton.boneInfoMap[boneName];

					skeleton.bones[ID].Offset = ConvertMatrixToGLMFormat(bone->mOffsetMatrix);

					for (unsigned int k = 0; k < bone->mNumWeights; k++)
					{
						int VertexID = bone->mWeights[k].mVertexId;
						float weight = bone->mWeights[k].mWeight;

						vertices[i][VertexID].SetVertexBoneData(ID, weight);
					}
				}
			}
		}
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			m_Meshes.push_back(Mesh(vertices[i], indices[i], textures));
		}

		std::string lastAnimation;

		for (unsigned int i = 0; i < scene->mNumAnimations; i++)
		{
			aiAnimation* AIanimation = scene->mAnimations[i];
			std::string animationName = AIanimation->mName.C_Str();
			Animation* anim = new Animation();
			anim->Duration = static_cast<float>(AIanimation->mDuration);
			anim->TicksPerSecond = static_cast<float>(AIanimation->mTicksPerSecond);

			anim->Keys.resize(AIanimation->mNumChannels);
			for (unsigned int j = 0; j < AIanimation->mNumChannels; j++)
			{
				aiNodeAnim* channel = AIanimation->mChannels[j];
				anim->Keys[j].BoneName = channel->mNodeName.C_Str();
				for (unsigned int k = 0; k < channel->mNumPositionKeys; k++)
				{
					TranslationKey key;
					key.TimeFrame = static_cast<float>(channel->mPositionKeys[k].mTime);
					key.Translation = ConvertVec3ToGLMFormat(channel->mPositionKeys[k].mValue);
					anim->Keys[j].TranslationKeys.push_back(key);
				}
				for (unsigned int k = 0; k < channel->mNumRotationKeys; k++)
				{
					RotationKey key;
					key.TimeFrame = static_cast<float>(channel->mRotationKeys[k].mTime);
					key.Rotation = ConvertQuatToGLMFormat(channel->mRotationKeys[k].mValue);
					anim->Keys[j].RotationKeys.push_back(key);
				}
				for (unsigned int k = 0; k < channel->mNumScalingKeys; k++)
				{
					ScaleKey key;
					key.TimeFrame = static_cast<float>(channel->mScalingKeys[k].mTime);
					key.Scale = ConvertVec3ToGLMFormat(channel->mScalingKeys[k].mValue);
					anim->Keys[j].ScaleKeys.push_back(key);
				}
			}
			ResourceManager::AddAnimation( anim, fileName + animationName);
			lastAnimation = fileName + animationName;
		}
		
		skeleton.SetPose(lastAnimation, 0.);
	}
}

Model::Model(std::vector<Mesh> mesh, std::string texturepath)
{
	GeneratedMesh = true;
	//m_Name = mapname;
	directory = texturepath.substr(0, texturepath.find_last_of("/"));
	FullDirectory = texturepath;
	Texture texture = Texture(texturepath);
	texture.type = "texture_diffuse";
	texture.path = texturepath;

	for (int i = 0; i < mesh.size(); i++)
		mesh[i].AddTextures(texture);
	
	m_Meshes = mesh;
}

void Model::ProcessNode(int parent, aiNode* node)
{
	int newParent = parent;
	if (skeleton.boneInfoMap.find(node->mName.C_Str()) != skeleton.boneInfoMap.end())
	{
		Bone bone;
		bone.Parent = parent;

		glm::mat4 transform = glm::transpose(ConvertMatrixToGLMFormat(node->mTransformation));
		glm::vec3 skew;
		glm::vec4 pers;
		glm::decompose(transform, bone.Scale, bone.Rotation, bone.Translation, skew, pers);

		skeleton.bones.push_back(bone);
		newParent = static_cast<int>(skeleton.bones.size() - 1);

		skeleton.boneInfoMap[node->mName.C_Str()] = newParent;
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(newParent, node->mChildren[i]);
	}
}

void Model::Draw(Shader& shader)
{
	for (auto& mesh : m_Meshes)
	{
		mesh.Draw(shader);
	}
}

void Model::DrawLines()
{
	for (auto& mesh : m_Meshes)
	{
		mesh.DrawLines();
	}
}


std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName,const aiScene* scene)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		std::string filename = str.C_Str();
		Texture texture;
		if(str.C_Str())
		{
			if (auto astexture = scene->GetEmbeddedTexture(str.C_Str()))
			{
				texture = Texture(astexture);
			}
			else 
			{
				texture = Texture(directory + "/" + filename);
			}
			texture.type = typeName;
			texture.path = std::string(str.C_Str());
			
		}
		textures.push_back(texture);
	}
	return textures;

}
