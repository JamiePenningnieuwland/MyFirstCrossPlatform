
#include "Input.h"
#include <dirent.h>
#include <sstream>
#include <iostream>
#include "InputData.h"
#include <imgui.h>

namespace Input
{
	namespace Internal
	{
		InputData* inputData;
		glm::vec2 MouseDelta;
		glm::vec2 MousePosition;
		bool HoldMouse = false;

	}
	void Init(void* inputDataHandle)
	{
		Internal::inputData = (InputData*)(inputDataHandle);
	}
	void HoldMouseInput(bool b)
	{
		Internal::HoldMouse = b;
	}
	glm::vec2 GetMouseDelta()
	{
		return Internal::MouseDelta;
	}
	void Update()
	{
		if (Internal::HoldMouse != true)
		{
			glm::vec2 previousMousePos = Internal::MousePosition;
			Internal::MousePosition = Internal::inputData->MousePosition;
			Internal::MouseDelta = Internal::MousePosition - previousMousePos;
		}
		else Internal::MouseDelta = glm::vec2(0.f, 0.f);
	}
	bool GetKey(uint32_t keyID)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse)
			return false;
		return Internal::inputData->Keys[keyID];
	}
	glm::vec2 GetMousePosition()
	{
		return Internal::inputData->MousePosition;
	}
	bool GetMouseButton(uint32_t buttonID)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse)
			return false;
		return Internal::inputData->MouseButtons[buttonID];
	}
	void LockMouse(bool mouse)
	{
		//todo
	}



}