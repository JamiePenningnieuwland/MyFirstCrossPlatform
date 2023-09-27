#pragma once

#include "Engine/PhysicsDebug/BulletDebug.h"

class Shader;
class GameObject;
class DebugDrawManager
{
public:
	DebugDrawManager() = default;
	DebugDrawManager(btDiscreteDynamicsWorld* world, Shader* shader )
		:m_DynamicWorld(world)
		,Drawer(shader)
	{

		Drawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	}
	void Draw(GameObject*);
private:

	BulletDebugDraw Drawer;
	btDiscreteDynamicsWorld* m_DynamicWorld;
};