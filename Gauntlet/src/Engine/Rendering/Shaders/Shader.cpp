#include "Shader.h"
#include <fstream>
#include <streambuf>

Shader::Shader(std::string fileName)
{
	std::ifstream vertexFile("Resources/Shaders/" + fileName + ".vert");
	std::ifstream fragmentFile("Resources/Shaders/" + fileName + ".frag");

	std::string vertexSource((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
	std::string fragmentSource((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());

	LoadShader(vertexSource, fragmentSource);
	
}
Shader::Shader(std::string vertex, std::string fragment)
{
	LoadShader(vertex, fragment);
}
void Shader::LoadShader(std::string vertex, std::string fragment)
{
	m_VertexSource = vertex.c_str();
	m_FragmentSource = fragment.c_str();

	// Create the shader objects
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load and Compile shaders
	glShaderSource(vertexShader, 1, &m_VertexSource, NULL);
	glShaderSource(fragmentShader, 1, &m_FragmentSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// Check for errors in shaders
	GLint status;
	GLint logSize;
	GLchar* log = NULL;
	GLint size;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
		log = new char[logSize];
		glGetShaderInfoLog(vertexShader, logSize, &size, log);
		if (logSize > 1) {
			std::cout << log << std::endl;
		}
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logSize);
		log = new char[logSize];
		glGetShaderInfoLog(fragmentShader, logSize, &size, log);
		if (logSize > 1) {
			std::cout << log << std::endl;
		}
	}

	// Create shader program
	m_Program = glCreateProgram();
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);
	glLinkProgram(m_Program);


	// Check program linked correctly
	GLint proLog = 0;
	glGetProgramiv(m_Program, GL_LINK_STATUS, &proLog);
	if (proLog == GL_FALSE) {
		GLint logLen = 0;
		GLchar* logInfo = NULL;
		glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &logLen);
		logInfo = new char[logLen];
		glGetProgramInfoLog(m_Program, logLen, &logLen, logInfo);
		if (logLen > 0) {
			std::cout << logInfo << std::endl;
		}
	}

	// Set the program to be used
	glUseProgram(m_Program);


	// Shaders are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::UploadUniform(std::string name, glm::mat4 matrix) 
{
	if (m_UniformIDs.find(name) == m_UniformIDs.end())
	{
		m_UniformIDs[name] = glGetUniformLocation(m_Program, name.c_str());
	}
	glUniformMatrix4fv(m_UniformIDs[name], 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::UploadUniform(std::string name)
{
	if(m_UniformIDs.find(name) == m_UniformIDs.end())
	{
		m_UniformIDs[name] = glGetUniformLocation(m_Program, name.c_str());
	}
	glUniform1i(m_UniformIDs[name], 0);
}
void Shader::UploadUniform(std::string name, float v)
{
	if (m_UniformIDs.find(name) == m_UniformIDs.end())
	{
		m_UniformIDs[name] = glGetUniformLocation(m_Program, name.c_str());
	}
	glUniform1f(m_UniformIDs[name], v);
}
void Shader::UploadUniform(std::string name, int v)
{
	if (m_UniformIDs.find(name) == m_UniformIDs.end())
	{
		m_UniformIDs[name] = glGetUniformLocation(m_Program, name.c_str());
	}
	glUniform1i(m_UniformIDs[name], v);
}
void Shader::UploadUniform(std::string name, bool v)
{
	if (m_UniformIDs.find(name) == m_UniformIDs.end())
	{
		m_UniformIDs[name] = glGetUniformLocation(m_Program, name.c_str());
	}
	glUniform1i(m_UniformIDs[name], v);
}
void Shader::UploadUniform(std::string name, float matrix[])
{
	if (m_UniformIDs.find(name) == m_UniformIDs.end())
	{
		m_UniformIDs[name] = glGetUniformLocation(m_Program, name.c_str());
	}
	glUniformMatrix4fv(m_UniformIDs[name], 1, GL_FALSE, matrix);
}
void Shader::UploadUniform(std::string name, glm::vec3 vector)
{
	if (m_UniformIDs.find(name) == m_UniformIDs.end())
	{
		m_UniformIDs[name] = glGetUniformLocation(m_Program, name.c_str());
	}
	glUniform3f(m_UniformIDs[name], vector.x, vector.y, vector.z);
}