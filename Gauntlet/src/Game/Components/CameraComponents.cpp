#include "CameraComponents.h"
#include "Input.h"

#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

glm::mat4 CameraComponent::GetView()
{
	auto transform = m_Parent->GetComponent<TransformComponent>();
	glm::vec3 Position = transform->Position + ObjectPositionOffset;

	glm::mat4 translation = glm::translate(glm::mat4(1.f), Position);
	glm::mat4 OffsetMatrix = glm::translate(glm::mat4(1.f), Offset);
	glm::mat4 rotation = glm::toMat4(transform->Rotation);
	glm::mat4 Lookat = glm::lookAt(glm::vec3(0.f), -Offset, { 0.f,1.f,0.f });
	//order important
	return translation * rotation * OffsetMatrix * glm::inverse(Lookat);
}
void CameraControlComponent::Update(float deltaTime)
{
	if (m_CameraComponent->IsMain == true)
	{

		float xoffset = Input::GetMouseDelta().x;
		float yoffset = Input::GetMouseDelta().y;

		float sensitivity = 0.1f * deltaTime;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		Rotation.x += yoffset;
		Rotation.y -= xoffset;

		Rotation.x = glm::clamp(Rotation.x, glm::radians(-65.f), glm::radians(0.f));
		m_CameraComponent->Offset = glm::vec3(0.f, 0., -Distance) *
			glm::mat3(glm::rotate(glm::mat4(1.f), Rotation.x, glm::vec3(1.f, 0.f, 0.f)));

		m_Parent->GetComponent<TransformComponent>()->Rotation = glm::vec3(0.f, Rotation.y, 0.f);
	}

}