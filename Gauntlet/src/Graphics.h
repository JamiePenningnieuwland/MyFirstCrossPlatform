#pragma once
#include <string>
class Graphics
{
public:
	//some platforms use different size int so I specify the size
	Graphics(std::string name, uint32_t width, uint32_t height);
	bool ShouldClose();
	void SwapBuffers();
	void Shutdown();
private:
	uint32_t m_Width;
	uint32_t m_Height;
};

