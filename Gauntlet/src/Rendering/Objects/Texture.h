#pragma once
#include <string>
#include <stb_image.h>
#include <vector>
#include "gl.h"
class Texture
{
public:
	Texture() = default;
	Texture(std::string fileName);
	Texture(std::string filenames[6]);
	void Bind();
	bool IsCubeMap = false;
	
protected:
	int m_Width = 0;
	int m_Height = 0;
	int m_numChannels = 0;
	GLuint m_ID = 0;
};
