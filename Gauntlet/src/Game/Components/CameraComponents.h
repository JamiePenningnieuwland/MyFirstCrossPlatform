#pragma once
#include "BaseComponent.h"
#include "Engine/Rendering/Camera.h"
#include "Game/GameObjects/GameObject.h"
#include <string>


class GameObject;
class CameraComponent :public Component
{
public:
	GET_ID_FUNCTION(CameraComponent)
		CameraComponent(const CameraComponent&) = default;
	CameraComponent()
		: Cam()
		, Offset(0.f, 0.f, 0.f)
		, ObjectPositionOffset(0.f)
		, IsMain(false)
	{};

	virtual void Init() {};
	virtual void Destroy() {};
	virtual void Update(float deltaTime) {};

	glm::mat4 GetProjection() { return Cam.GetProjectionMatrix(); };
	glm::mat4 GetView();

	Camera Cam;

	glm::vec3 ObjectPositionOffset;
	glm::vec3 Offset;
	bool IsMain;
};

class CameraControlComponent :public Component
{
public:
	GET_ID_FUNCTION(CameraControlComponent)

		CameraControlComponent(const CameraControlComponent&) = default;
	CameraControlComponent(float dist = 10.f)
		: Distance(dist)
		, Rotation(glm::radians(30.), glm::radians(180.))
		, m_CameraComponent(nullptr)
	{}

	virtual void Init()
	{
		if (!m_Parent->HasComponent<CameraComponent>())
		{
			m_Parent->AddComponent<CameraComponent>();
		}
		m_CameraComponent = m_Parent->GetComponent<CameraComponent>();
		m_CameraComponent->Offset = glm::vec3(0.f, 0., Distance) * glm::mat3(glm::rotate(glm::mat4(1.f), Rotation.x, glm::vec3(1.f, 0.f, 0.f)) *
			glm::rotate(glm::mat4(1.f), Rotation.y, glm::vec3(0.f, 1.f, 0.f)));
	};
	virtual void Destroy() {};
	virtual void Update(float deltaTime);

	glm::vec2 rot;
	glm::vec2 secondRot;
	float Distance;
	glm::vec2 Rotation;

private:
	CameraComponent* m_CameraComponent;
};