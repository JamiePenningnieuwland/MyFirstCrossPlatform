#include "PhysicsComponents.h"
#include "Game/GameObjects/GameObject.h"

#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void PhysicsComponent::CopyTransform()
{
	auto transform = m_Parent->GetComponent<TransformComponent>();
	glm::vec3 newScale = transform->Scale * Scale;

	btVector3 scale = btVector3(newScale.x, newScale.y, newScale.z);
	ObjectShape->setLocalScaling(scale);

	glm::vec3 transOffset;
	{
		glm::mat3 transScale = glm::scale(glm::mat4(1.f), transform->Scale);
		glm::mat3 transRot = glm::inverse(glm::toMat3(transform->Rotation));
		transOffset = Offset * transRot * transScale;
	}


	btTransform btransform;
	btransform.setIdentity();
	glm::vec3 transpos = transform->Position + transOffset;
	btVector3 pos = btVector3
	(
		transpos.x,
		transpos.y,
		transpos.z
	);
	btQuaternion rot = btQuaternion
	(
		transform->Rotation.x,
		transform->Rotation.y,
		transform->Rotation.z,
		transform->Rotation.w
	);
	btransform.setOrigin(pos);
	btransform.setRotation(rot);
	Objectbody->setWorldTransform(btransform);
}
void PhysicsComponent::Init()
{
	//auto Transform = m_Parent->GetComponent<TransformComponent>();
	switch (Shape)
	{
	case Geometry::Box:
		ObjectShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
		break;
	case Geometry::Sphere:
		ObjectShape = new btSphereShape(1.f);
		break;
	case Geometry::Capsule:
		ObjectShape = new btCapsuleShape(1.f, 1.f);
		break;
	default:
		ObjectShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
		break;
	}
	//ObjectShape = new btBoxShape(btVector3(0.5f, 0.5f,0.5f));

	btTransform ObjectTransform;
	ObjectTransform.setIdentity();

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		ObjectShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(ObjectTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, ObjectShape, localInertia);
	Objectbody = new btRigidBody(rbInfo);
	CopyTransform();
	AttachToPhysicsWorld();
}

void PhysicsComponent::CopyTransformFromPhysicsWorld()
{
	//Objectbody->setAngularVelocity(btVector3(btScalar(!LockXRotation), btScalar(!LockYRotation), btScalar(!LockZRotation)) * Objectbody->getAngularVelocity());
	//Objectbody->setAngularFactor(btVector3(btScalar(!LockXRotation), btScalar(!LockYRotation), btScalar(!LockZRotation)));
	//Objectbody->setFriction(0.f);
	//Objectbody->setDamping(btVector3(1.f,1.f,1.f),btVector3(btScalar(LockXRotation), btScalar(LockYRotation), btScalar(LockZRotation)));

	glm::vec3 transOffset;
	{
		auto transform = m_Parent->GetComponent<TransformComponent>();
		glm::mat3 transScale = glm::scale(glm::mat4(1.f), transform->Scale);
		glm::mat3 transRot = glm::inverse(glm::toMat3(transform->Rotation));
		transOffset = Offset * transRot * transScale;
	}

	btTransform transform;
	transform = Objectbody->getWorldTransform();
	m_Parent->GetComponent<TransformComponent>()->Rotation = (glm::quat((float)transform.getRotation().w(), (float)transform.getRotation().x(), (float)transform.getRotation().y(), (float)transform.getRotation().z()));
	m_Parent->GetComponent<TransformComponent>()->Position = (glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()) - transOffset);
}

void PhysicsComponent::AttachToPhysicsWorld()
{
	dynamicWorld->addRigidBody(Objectbody);

}
void PhysicsComponent::Destroy()
{
	//looked at github example https://github.com/bulletphysics/bullet3/blob/master/examples/HelloWorld/HelloWorld.cpp

	btCollisionObject* obj = Objectbody;
	btRigidBody* body = btRigidBody::upcast(obj);
	if (body && body->getMotionState())
	{
		delete body->getMotionState();
	}
	dynamicWorld->removeCollisionObject(obj);
	delete obj;

	//delete collision shapes
	btCollisionShape* shape = ObjectShape;
	delete shape;

	// dynamicWorld;
}