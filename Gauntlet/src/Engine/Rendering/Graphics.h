#pragma once
#include "imgui.h"
#include <string>


class Graphics
{
public:
	//some platforms use different size int so I specify the size
	Graphics() = default;
	Graphics(std::string name, uint32_t width, uint32_t height);
	bool ShouldClose();
	void imGUI_initalize()
	{
		ImGuiIO io = ImGui::GetIO();
		//auto mediumfont = io.Fonts->AddFontFromFileTTF("Resources/Fonts/OpenSans/OpenSans-Medium.ttf", 18.0f);
		//io.Fonts->AddFontFromFileTTF("Resources/Fonts/OpenSans/OpenSans-bold.ttf", 18.0f);
		//io.FontDefault = mediumfont;
	}
	void SwapBuffers();
	void BeginImGuiFrame();
	void RenderImGUI();
	void Shutdown();
	uint32_t GetWidth() const { return m_Width; }
	uint32_t GetHeight() const { return m_Height; }
	void ChangeWindowSize(uint32_t w, uint32_t h)
	{
		m_Width = w;
		m_Height = h;
	}
private:
	uint32_t m_Width;
	uint32_t m_Height;
};

