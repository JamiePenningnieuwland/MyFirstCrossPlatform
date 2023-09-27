#pragma once
#include <glm/vec2.hpp>
struct InputData
{
	InputData() 
		: MousePosition({0., 0.})
	{
		Flush();
	}

	void Flush()
	{
		for (int i = 0; i < 512; i++)
		{
			Keys[i] = false;
		}
		for (int i = 0; i < 8; i++)
		{
			MouseButtons[i] = false;
		}
	}

	bool Keys[512];
	glm::vec2 MousePosition;
	bool MouseButtons[8];
};