#pragma once
#include <string>

#pragma warning(push, 0)
#include <stb_image.h>
#pragma warning(pop)

#include <vector>
#include "gl.h"
#include <assimp/texture.h>
class Texture
{
public:
	Texture() = default;
	Texture(std::string fileName/*,std::string directory*//*, std::string mapName*/);
	Texture(const aiTexture* texture);
	Texture(std::string filenames[6]);

	void Bind();
	bool IsCubeMap = false;
	//std::string GetName() { return name; }
    GLuint GetID() const {  return m_ID; }
	std::string type;
	std::string path;
protected:
	void UploadData(unsigned char* data);
	//std::string name;
	int m_Width = 0;
	int m_Height = 0;
	int m_numChannels = 0;
	GLuint m_ID = 0;
};
