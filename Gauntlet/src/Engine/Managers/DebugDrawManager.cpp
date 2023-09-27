#include "DebugDrawManager.h"
#include "Engine/PhysicsDebug/BulletDebug.h"
#include <Game/Components/Components.h>
#include "Game/GameObjects/GameObject.h"


void DebugDrawManager::Draw(GameObject* obj)
{
	m_DynamicWorld->setDebugDrawer(&Drawer);
	m_DynamicWorld->debugDrawWorld();
	auto comp = obj->GetComponent<PhysicsComponent>();
	m_DynamicWorld->debugDrawObject(comp->Objectbody->getWorldTransform(), comp->ObjectShape, btVector3(1.f, 0., 0.));
}