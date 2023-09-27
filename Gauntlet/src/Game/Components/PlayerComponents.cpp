#include "PlayerComponents.h"
#include "Game/GameObjects/GameObject.h"
#include "Game/Components/PhysicsComponents.h"

#include <btBulletCollisionCommon.h>
#include <Input.h>
#include <glm/gtx/quaternion.hpp>
#include <Game/Components/RenderComponents.h>


template<typename T>
T Lerp(T min, T max, float t)
{
	return (max - min) * t + min;
}

void PlayerControllerComponent:: Init()
{
	btRigidBody* body = m_Parent->GetComponent<PhysicsComponent>()->Objectbody;

	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CHARACTER_OBJECT);
	body->setActivationState(DISABLE_DEACTIVATION);
};

void PlayerControllerComponent::Update(float deltaTime)
{
	if (!IsActive)
		return;

	m_Parent->GetComponent<PhysicsComponent>()->Objectbody->setAngularVelocity(btVector3(0.f, 0.f, 0.f));

	glm::vec3 newPosition(0.f, 0.f, 0.f);
	glm::vec3 direction(0.f, 0.f, 0.f);
	glm::vec2 inputChange(0.f);

	//input
	if (Input::GetKey(KEY_D))
	{
		inputChange.x -= 1.f;
	}

	if (Input::GetKey(KEY_A))
	{
		inputChange.x += 1.f;
	}

	if (Input::GetKey(KEY_W))
	{
		inputChange.y += 1.f;
	}

	if (Input::GetKey(KEY_S))
	{
		inputChange.y -= 1.f;
	}
	auto physicobj = m_Parent->GetComponent<PhysicsComponent>();
	auto transform = m_Parent->GetComponent<TransformComponent>();


	if (Input::GetKey(KEY_SPACE))
	{
		// took example from  https://gamedev.stackexchange.com/questions/58012/detect-when-a-bullet-rigidbody-is-on-ground
		int numManifolds = physicobj->Dispatcher->getNumManifolds();
		for (int i = 0; i < numManifolds; i++)
		{
			btPersistentManifold* contactManifold = physicobj->dynamicWorld->getDispatcher()->getManifoldByIndexInternal(i);
			btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
			btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

			if (obA == physicobj->Objectbody || obB == physicobj->Objectbody) {
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					btManifoldPoint& pt = contactManifold->getContactPoint(j);
					if (pt.getDistance() < 0.f)
					{

						btVector3 normal;


						if (obB == physicobj->Objectbody)
							normal = -pt.m_normalWorldOnB;
						else
							normal = pt.m_normalWorldOnB;


						if (normal.y() > 0.4f /*put the threshold here */)
						{
							float jump = 0;
							jump = 3.f;
							//m_Parent->GetComponent<TransformComponent>()->Position.y = Lerp(jump,m_Parent->GetComponent<TransformComponent>()->Position.y, 10 * deltaTime);
						}
					}
				}
			}
		}
	}

	if (glm::length2(inputChange) > 0.1f)
	{

		glm::vec3 oldpos = m_Parent->GetComponent<TransformComponent>()->Position;
		direction = glm::vec3(inputChange.x, 0.f, inputChange.y) * glm::inverse(glm::toMat3(transform->Rotation));
		newPosition = oldpos + (glm::normalize(direction) * Strength);
		m_Parent->GetComponent<TransformComponent>()->Position = Lerp(oldpos, newPosition, deltaTime);
		if (m_Parent->HasComponent<AnimationRenderComponent>())
			m_Parent->GetComponent<AnimationRenderComponent>()->isPlaying = true;
	}
	else
	{
		if (m_Parent->HasComponent<AnimationRenderComponent>())
			m_Parent->GetComponent<AnimationRenderComponent>()->isPlaying = false;
	}

}