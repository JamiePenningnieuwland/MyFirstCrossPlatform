#include "ResourceManager.h"
#include "Engine/Rendering/Models/Model.h"
#include "Engine/Rendering/Models/Texture.h"
#include "Engine/Rendering/Models/Animation.h"


std::map<std::string, Animation*> ResourceManager::s_Animations;
std::map<std::string, Model*> ResourceManager::s_Models;

namespace Loading
{
	Model* LoadModel(bool generatemesh, std::string filepath);
};
void ResourceManager::AddAnimation(Animation* animation, std::string name)
{
	if(s_Animations.find(name) !=s_Animations.end())
	{
		printf("Animation already exists\n");
		return;
	}
	s_Animations[name] = animation;
}
Animation* ResourceManager::GetAnimation(std::string name)
{
	if (s_Animations.find(name) != s_Animations.end())
	{
		return s_Animations[name];
	}
	return nullptr;
}
void ResourceManager::clear()
{
	for(auto& [key, value]: s_Models)
	{
		delete s_Models[key];
	}
	s_Models.clear();

	for(auto& [key, value]: s_Animations)
	{
		delete s_Animations[key];
	}
	s_Animations.clear();
}

void ResourceManager::AddModel(/*Model* model,*/ bool generated, std::string name)
{
	if (s_Models.find(name) != s_Models.end())
	{
		printf("Animation already exists\n");
		return;
	}

	Model* model = Loading::LoadModel(generated, name);
	s_Models[name] = model;
}

Model* ResourceManager::GetModel(std::string name)
{
	if (s_Models.find(name) != s_Models.end())
	{
		return s_Models[name];
	}
	return nullptr;
}

const std::map<std::string, Animation*>& ResourceManager::GetAnimationMap()
{
	return s_Animations;
}

Model* Loading::LoadModel(bool generatemesh, std::string filepath)
{
	Model* model;
	if (generatemesh)
	{
		//should add genometry
		std::vector<Vertex> vertices =
		{

			//plane1
			{ { -0.5f, -0.5f,0.5f }, {0., 0., 1.}, {0., 0.}, {1.,0.,0.}, {0.,1.,0.}},
			{ { -0.5f, 0.5f, 0.5f }, {0., 0., 1.}, {0., 1.}, {1.,0.,0.}, {0.,1.,0.}},
			{ { 0.5f, -0.5f, 0.5f }, {0., 0., 1.}, {1., 0.}, {1.,0.,0.}, {0.,1.,0.}},
			{ { 0.5f,  0.5f, 0.5f }, {0., 0., 1.}, {1., 1.}, {1.,0.,0.}, {0.,1.,0.}},

			//plane2
			{ { -0.5f, -0.5f, -0.5f }, {0., 0., -1.}, {0., 0.}, {-1.,0.,0.}, {0.,1.,0.}},
			{ { -0.5f, 0.5f,  -0.5f }, {0., 0., -1.}, {0., 1.}, {-1.,0.,0.}, {0.,1.,0.}},
			{ { 0.5f, -0.5f,  -0.5f }, {0., 0., -1.}, {1., 0.}, {-1.,0.,0.}, {0.,1.,0.}},
			{ { 0.5f,  0.5f,  -0.5f }, {0., 0., -1.}, {1., 1.}, {-1.,0.,0.}, {0.,1.,0.}},

			//plane3
			{ { -0.5f, -0.5f, -0.5},  {-1., 0., 0.}, {0., 0.}, {0.,0.,-1.}, {0.,1.,0.}},
			{ { -0.5f, 0.5f,  -0.5},  {-1., 0., 0.}, {0., 1.}, {0.,0.,-1.}, {0.,1.,0.}},
			{ { -0.5f, -0.5f, 0.5f }, {-1., 0., 0.}, {1., 0.}, {0.,0.,-1.}, {0.,1.,0.}},
			{ { -0.5f,  0.5f, 0.5f }, {-1., 0., 0.}, {1., 1.}, {0.,0.,-1.}, {0.,1.,0.}},

			//plane4
			{ { 0.5f, -0.5f, -0.5},  {1., 0., 0.}, {0., 0.}, {0.,0.,1.}, {0.,1.,0.}},
			{ { 0.5f, 0.5f,  -0.5},  {1., 0., 0.}, {0., 1.}, {0.,0.,1.}, {0.,1.,0.}},
			{ { 0.5f, -0.5f, 0.5f }, {1., 0., 0.}, {1., 0.}, {0.,0.,1.}, {0.,1.,0.}},
			{ { 0.5f,  0.5f, 0.5f }, {1., 0., 0.}, {1., 1.}, {0.,0.,1.}, {0.,1.,0.}},

			//plane5
			{ { -0.5f, -0.5f, -0.5f},  {0., -1., 0.}, {0., 0.}, {1.,0.,0.}, {0.,0.,-1.}},
			{ { -0.5f, -0.5f, 0.5f },  {0., -1., 0.}, {0., 1.}, {1.,0.,0.}, {0.,0.,-1.}},
			{ { 0.5f, -0.5f,  -0.5f }, {0., -1., 0.}, {1., 0.}, {1.,0.,0.}, {0.,0.,-1.}},
			{ { 0.5f,  -0.5f, 0.5f },  {0., -1., 0.}, {1., 1.}, {1.,0.,0.}, {0.,0.,-1.}},

			////plane6
			{ { -0.5f, 0.5f, -0.5f},  {0., 1., 0.}, {0., 0.}, {1.,0.,0.}, {0.,0.,1.}},
			{ { -0.5f, 0.5f, 0.5f },  {0., 1., 0.}, {0., 1.}, {1.,0.,0.}, {0.,0.,1.}},
			{ { 0.5f, 0.5f,  -0.5f }, {0., 1., 0.}, {1., 0.}, {1.,0.,0.}, {0.,0.,1.}},
			{ { 0.5f,  0.5f, 0.5f },  {0., 1., 0.}, {1., 1.}, {1.,0.,0.}, {0.,0.,1.}},

		};

		std::vector<GLuint> indices =
		{ 0,  2,  1,  3,  1,  2,
			4,  5,  6,  7,  6,  5,
			8,  10,  9, 11, 9,	10,
			12, 13, 14, 15, 14, 13,
			16, 18, 17, 19, 17, 18,
			20, 21, 22, 23, 22, 21
		};

		Mesh mesh(vertices, indices);
		model = new Model({ mesh }, filepath);
	}
	else
	{
		model = new Model(filepath);
	}
	return model;

}