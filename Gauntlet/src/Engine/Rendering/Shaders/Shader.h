#pragma once
#include <string>
#include <iostream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gl.h"

class Shader
{
public:
	Shader() = default;
	Shader(std::string vertex, std::string fragment);
	Shader(std::string fileName);

	void LoadShader(std::string vertex, std::string fragment);
	const GLuint GetProgram() { return m_Program; }
	const char* GetVertexSrc() { return m_VertexSource; }
	const char* GetFragmentSrc() { return m_FragmentSource; }

	void Bind() 
	{
		glUseProgram(m_Program);
	}
	void UploadUniform(std::string name, bool v);
	void UploadUniform(std::string name);

	void UploadUniform(std::string name, int v);
	void UploadUniform(std::string name, glm::mat4 matrix);
	void UploadUniform(std::string name, glm::vec3 vector);
	void UploadUniform(std::string name, float v);
	void UploadUniform(std::string name, float matrix[]);


private:
	GLuint m_Program;
	const char* m_VertexSource;
	const char* m_FragmentSource;
	std::map<std::string, GLuint> m_UniformIDs;
};

