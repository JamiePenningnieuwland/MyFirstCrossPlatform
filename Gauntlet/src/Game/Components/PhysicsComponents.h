#pragma once
#include "BaseComponent.h"
#include <glm/vec3.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class GameObject;

enum class Geometry
{
	Box = 1,
	Sphere = 2,
	Capsule = 3,
};


class PhysicsComponent :public Component
{
public:
	GET_ID_FUNCTION(PhysicsComponent)

		PhysicsComponent(const PhysicsComponent&) = default;
	PhysicsComponent(float m, btDiscreteDynamicsWorld* world, btCollisionDispatcher* dispatcher, Geometry type)
		: mass(m)
		, Scale(1., 1., 1)
		, Offset(0., 0., 0.)
		, dynamicWorld(world)
		, Dispatcher(dispatcher)
		, ObjectShape(nullptr)
		, Objectbody(nullptr)
		, Shape(type)
		//, debugModel(nullptr)
	{}
	virtual void Init();
	virtual void Update(float deltaTime) {};
	virtual void Destroy();

	void CopyTransform();
	void CopyTransformFromPhysicsWorld();

	void AttachToPhysicsWorld();
	btCollisionWorld::ClosestRayResultCallback RayCollisionTest(btVector3, btVector3);
	btCollisionShape* ObjectShape;
	btRigidBody* Objectbody;
	btDiscreteDynamicsWorld* dynamicWorld;
	btCollisionDispatcher* Dispatcher;


	glm::vec3 Scale;
	glm::vec3 Offset;
	float mass;
	Geometry Shape = Geometry::Box;

	bool LockXRotation = false;
	bool LockYRotation = false;
	bool LockZRotation = false;

};
