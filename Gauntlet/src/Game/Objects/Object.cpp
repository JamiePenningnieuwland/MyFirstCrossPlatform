#include "Object.h"
#include "Input.h"

void Object::UpdateMatrix()
{
	
}

glm::mat4 Object::GetModelMatrix()
{
	glm::mat4 translation = glm::translate(glm::mat4(1.f), m_Position);
	glm::mat4 OffsetMatrix = glm::translate(glm::mat4(1.f), -m_Offset);
	glm::mat4 scale = glm::scale(glm::mat4(1.f), m_Scale);
	glm::mat4 rotation = glm::toMat4(m_Rotation);

	//order important
	return translation * rotation * scale * OffsetMatrix;
}
void Object::Update(float deltaTime)
{
	//ProcessInput(deltaTime);
	btTransform transform;
	transform = m_PhysicsObj.Objectbody->getWorldTransform();
	m_Rotation = (glm::quat(transform.getRotation().w(), transform.getRotation().x(), transform.getRotation().y(), transform.getRotation().z()));
	m_Position = (glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()));

}
void Object::Draw(Shader& shader)
{
	shader.UploadUniform("Model", GetModelMatrix());
	m_Texture->Bind();
	m_Model->Draw();
}
void Object::DebugDraw(Shader& debug, Model* debugModel)
{
	debug.UploadUniform("Model", m_PhysicsObj.matrix());
	debugModel->DrawLines();
}
void Object::ProcessInput(float deltaTime)
{
	float strength = 10.f;
	glm::vec3 force(0.f);

	//input
	if (Input::GetKey(KEY_KP_6))
	{
		force.x += 1.f;
	}
	if (Input::GetKey(KEY_KP_4))
	{
		force.x -= 1.f;
		
	}
	if (Input::GetKey(KEY_KP_8))
	{
		force.z -= 1.f;
	}
	if (Input::GetKey(KEY_KP_2))
	{
		force.z += 1.f;
	}
	if (glm::length2(force) > 0.1f)
	{
		force = force * glm::toMat3(GetRotation());
		force = glm::normalize(force);
		force *= deltaTime * strength;
		m_PhysicsObj.Objectbody->setActivationState(1);
		m_PhysicsObj.Objectbody->applyImpulse(btVector3(btScalar(force.x), btScalar(force.y), btScalar(force.z)), btVector3(0., 0., 0.));
	}

}


