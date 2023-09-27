#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
public:
	Camera(float Fov = 70.f, float AspectRatio = 1.f, float Near = 0.01f, float Far = 100.f)
		: m_Fov(Fov)
		, m_AspectRatio(AspectRatio)
		, m_Near(Near)
		, m_Far(Far)
	{}

	const glm::mat4 GetProjectionMatrix();
	float GetFov() const { return m_Fov; }
	void SetFov(float fov) { m_Fov = fov; }

	float GetAspectRatio() const { return m_AspectRatio; }
	void SetAspectRatio(float aspectr) { m_AspectRatio = aspectr; }

	float GetNear() const { return m_Near; }
	void SetNear(float near) { m_Near = near; }

	float GetFar() const { return m_Far; }
	void SetFar(float far) { m_Far = far; }

	glm::mat4 GetView()
	{
		glm::mat4 view = glm::mat4(1.0f);
		return glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	}
private:
	
	float m_Fov;
	float m_AspectRatio;
	float m_Near, m_Far;
};

