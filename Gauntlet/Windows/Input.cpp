#include "Input.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "../ExternalFiles/IamGUI/imgui.h"

namespace Input
{
	namespace Internal
	{
		GLFWwindow* g_Window;
		glm::vec2 g_MousePosition;
		glm::vec2 g_MouseDelta;
		bool HoldMouse = false;
	}
	
	void Init(void* windowHandle)
	{
		Internal::g_Window = (GLFWwindow*)(windowHandle); 
		Internal::g_MouseDelta = glm::vec2(0.f);
		Internal::g_MousePosition = glm::vec2(0.f);
	}
	bool GetKey(uint32_t keyID)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureKeyboard)
			return false;
	
		return (glfwGetKey(Internal::g_Window, keyID) == GLFW_PRESS);
		
	}
	void HoldMouseInput(bool b)
	{
		Internal::HoldMouse = b;
	}
	glm::vec2 GetMouseDelta()
	{
		return Internal::g_MouseDelta;
	}
	void Update()
	{
		if (Internal::HoldMouse != true)
		{
			double x, y;
			glfwGetCursorPos(Internal::g_Window, &x, &y);
			glm::vec2 previousMousePos = Internal::g_MousePosition;
			Internal::g_MousePosition = glm::vec2(x, y);
			Internal::g_MouseDelta = Internal::g_MousePosition - previousMousePos;
		}
		else(Internal::g_MouseDelta = { 0.f,0.f });

	}
	void LockMouse(bool lock)
	{
		if (lock)
		{
			glfwSetInputMode(Internal::g_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(Internal::g_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	glm::vec2 GetMousePosition()
	{
		
		return Internal::g_MousePosition;
	}
	bool GetMouseButton(uint32_t buttonID)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse)
			return false;

		return (glfwGetMouseButton(Internal::g_Window, buttonID) == GLFW_PRESS);
	}

}