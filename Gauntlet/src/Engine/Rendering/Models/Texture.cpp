#include "Texture.h"
#include "Engine/Rendering/Shaders/Shader.h"
Texture::Texture(/*std::string fileName,*/ std::string directory/*, std::string mapName*/)
{
	std::string filename;// = std::string(fileName);
	filename = directory;// +"/" + filename;
	//name = mapName;
	//loading pixeldata
	unsigned char* Data = nullptr;
	//use load from memory with other formats like fbx

	Data = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_numChannels, 3);
	UploadData(Data);
	
}
Texture::Texture(const aiTexture* texture)
{
	
	//loading pixeldata
	unsigned char* Data = nullptr;
	const stbi_uc* test = (const stbi_uc*)texture->pcData;

	Data = stbi_load_from_memory(test, texture->mWidth, &m_Width, &m_Height, &m_numChannels, 3);
	//use load from memory with other formats like fbx
	//Data = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_numChannels, 3);
	UploadData(Data);
}
void Texture::UploadData(unsigned char* data)
{
	if (data)
	{
		GLenum format;
		if (m_numChannels == 1)
			format = GL_RED;
		else if (m_numChannels == 3)
			format = GL_RGB;
		else if (m_numChannels == 4)
			format = GL_RGBA;

		//creating the texture on gpu
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//uploadng pixeldata 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		//free memory since the gpu holds the data
		stbi_image_free(data);
	}
}

void Texture::Bind()
{
	 glBindTexture(GL_TEXTURE_2D, m_ID);
}

Texture::Texture(std::string cubeFaces[6])
{
	//Creating texture on gpu
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);

	//loading pixeldata
	unsigned char* data;
	for (unsigned int i = 0; i < 6; i++)
	{
		data = stbi_load(cubeFaces[i].c_str(), &m_Width, &m_Height, &m_numChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}
