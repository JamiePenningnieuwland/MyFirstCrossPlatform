#include "Camera.h"
#include "Input.h"
#include <math.h>

const glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_Near, m_Far);
}

