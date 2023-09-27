#pragma once

#include <glm/vec3.hpp>
#include <string>
#include <vector>

#include <btBulletDynamicsCommon.h>


class GameObject;
class Texture;
class Model;
struct vec3;


class MapLoader
{
public:
	std::vector<GameObject*> LoadTiles(glm::vec3* tiles, int size, btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis);
	std::vector<GameObject*> LoadTiledMap(int tiles[1024], btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis);
	GameObject* MakeTileObject(glm::vec3 position, glm::vec3 scale, std::string filepath, btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis);

	//Texture* generateTexture();

private:

};
class SpawnLoaders
{
public:
	std::vector<GameObject*> LoadSpawners(btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis);
	GameObject* LoadSpawner(btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis);
	GameObject* MakeSpawnObject(glm::vec3 position, glm::vec3 scale, btDiscreteDynamicsWorld* world, btCollisionDispatcher* dis);
private:
	btRigidBody* AddRigidBody(btVector3 position, btDiscreteDynamicsWorld* world);
	void generatePosition(GameObject* object,btCollisionDispatcher*);

};