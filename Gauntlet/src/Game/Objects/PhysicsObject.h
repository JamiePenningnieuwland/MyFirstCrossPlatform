#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtx/quaternion.hpp>
#include <btBulletDynamicsCommon.h>

struct PhysicsObject
{
	btCollisionShape* ObjectShape;
	btRigidBody* Objectbody;
	glm::vec3 Scale;
	glm::mat4 matrix()
	{
		btTransform transform;
		transform = Objectbody->getWorldTransform();
		glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()));
		glm::mat4 scale = glm::scale(glm::mat4(1.f), Scale);
		glm::mat4 rotation = glm::toMat4(glm::quat(transform.getRotation().w(), transform.getRotation().x(), transform.getRotation().y(), transform.getRotation().z()));

		//order important
		return translation * rotation * scale;
		 
	}
};