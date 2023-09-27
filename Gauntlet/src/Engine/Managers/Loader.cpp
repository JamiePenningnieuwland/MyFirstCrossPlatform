#include "Loader.h"
#include <Game/GameObjects/GameObject.h>
#include "Engine/Rendering/Models/Model.h"
#include <Engine/Rendering/Models/Texture.h>
#include <Game/Components/Components.h>
#include "Engine/Managers/ResourceManager.h"
#include "Engine/MathUtils.h"

//std::vector<GameObject*> MapLoader::LoadTiles(glm::vec3* tiles, int size, btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis)
//{
//	std::vector<GameObject*> gameObjects;
//
//	ResourceManager::AddModel(true, "Resources/Textures/Texture.jpg");
//	glm::vec3 pos = glm::vec3(-16.f, 0.f, -16.f);
//	glm::vec3 scale = glm::vec3(8.f, 0.5f, 8.f);
//	gameObjects.push_back(MakeTileObject(pos, scale, world, dis));
//
//	for (int i = 0; i < size; i++)
//	{
//		glm::vec3 pos = tiles[i] * glm::vec3(4.f);
//		glm::vec3 scale(4.f, 1.f, 4.f);
//		gameObjects.push_back(MakeTileObject(pos, scale, world, dis));
//	}
//	return gameObjects;
//}
std::vector<GameObject*> MapLoader::LoadTiledMap(int tiles[1024], btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis)
{
	std::vector<GameObject*> gameObjects;
	std::string Ground = "Resources/Textures/GoblinSpawn.jpg";
	std::string wall = "Resources/Textures/Texture.jpg";
	ResourceManager::AddModel(true, wall);
	ResourceManager::AddModel(true, Ground);
	glm::vec3 scale1 = glm::vec3(128.f, 1.f, 128.f);
	glm::vec3 pos1 = glm::vec3(0.f, 0.f, 0.f);/* * scale1;*/
	gameObjects.push_back(MakeTileObject(pos1, scale1,Ground, world, dis));

	for (int z = 0; z < 32; z++)
	{
		for (int x = 0; x < 32; x++)
		{
			int index = x + z * 32;
			if (tiles[index] > 0)
			{
				glm::vec3 scale(4.f, 8.f, 4.f);
				glm::vec3 pos2 = glm::vec3(static_cast<float>(x) - 16.f, 0.5f, static_cast<float>(z) - 16.F) * scale;
				gameObjects.push_back(MakeTileObject(pos2, scale,wall, world, dis));
			}
		}
	}
	return gameObjects;
}
btRigidBody* SpawnLoaders::AddRigidBody(btVector3 position, btDiscreteDynamicsWorld* world)
{
	btRigidBody* Objectbody;
	btCollisionShape* shape = new btBoxShape(btVector3(0.75f, 0.75f, 0.75f));
	btVector3 localInertia(0, 0, 0);
	btTransform ObjectTransform;
	ObjectTransform.setIdentity();
	ObjectTransform.setOrigin(position);
	shape->calculateLocalInertia(0.f, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(ObjectTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0.f, myMotionState, shape, localInertia);

	Objectbody = new btRigidBody(rbInfo);
	world->addRigidBody(Objectbody);
	return Objectbody;
}
GameObject* SpawnLoaders::LoadSpawner(btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis)
{
	ResourceManager::AddModel(true, "Resources/Textures/default.jpg");

	glm::vec2 randpos = glm::vec2(MathUtils::RandomRangedFloat(32.f), MathUtils::RandomRangedFloat(32.f));
	glm::vec3 position = glm::vec3(randpos.x, 1.25f, randpos.y);
	GameObject* object = MakeSpawnObject(position, glm::vec3(1.5f, 1.5f, 1.5f), world, dis);
	generatePosition(object, dis);
	return object;
}

void SpawnLoaders::generatePosition(GameObject* object, btCollisionDispatcher* dis)
{
	
	int numManifolds = object->GetComponent<PhysicsComponent>()->Dispatcher->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = dis->getManifoldByIndexInternal(i);
		btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

		if (obA == object->GetComponent<PhysicsComponent>()->Objectbody || obB == object->GetComponent<PhysicsComponent>()->Objectbody)
		{
			glm::vec2 randpos = glm::vec2(MathUtils::RandomRangedFloat(32.f), MathUtils::RandomRangedFloat(32.f));
			glm::vec3 position = glm::vec3(randpos.x, 1.25f, randpos.y);
			object->GetComponent<TransformComponent>()->Position = position;
			generatePosition(object, dis);
		}
	}
}



std::vector<GameObject*> SpawnLoaders::LoadSpawners(btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis)
{
	std::vector<GameObject*> spawners;
	glm::vec2 randpos = glm::vec2(MathUtils::RandomRangedFloat(32.f), MathUtils::RandomRangedFloat(32.f));
	glm::vec3 position = glm::vec3(randpos.x, 1.25f, randpos.y);
	GameObject* object  = MakeSpawnObject(position, glm::vec3(1.5f, 1.5f, 1.5f), world, dis);
	spawners.push_back(object);

	//generatePosition(object, dis);

	return spawners;
}

GameObject* MapLoader::MakeTileObject(glm::vec3 position, glm::vec3 scale, std::string filepath, btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis)
{
	GameObject* object = new GameObject("Tile");
	object->AddComponent<RenderComponent>(ResourceManager::GetModel(filepath));
	object->GetComponent<TransformComponent>()->Position = position;
	object->GetComponent<TransformComponent>()->Scale = scale;
	object->AddComponent<PhysicsComponent>(0.f, world, dis, Geometry::Box);
	return object;
}
GameObject* SpawnLoaders::MakeSpawnObject(glm::vec3 position, glm::vec3 scale, btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis)
{
	GameObject* object = new GameObject("Spawner");
	object->AddComponent<RenderComponent>(ResourceManager::GetModel("Resources/Textures/default.jpg"));
	object->GetComponent<TransformComponent>()->Position = position;
	object->GetComponent<TransformComponent>()->Scale = scale;
	object->AddComponent<PhysicsComponent>(0.f, world, dis, Geometry::Box);
	return object;
}