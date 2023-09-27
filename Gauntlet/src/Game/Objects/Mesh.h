#pragma once
#include "gl.h"
#include "Texture.h"
#include "Rendering/Shaders/Shader.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
};

class Mesh
{

public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	void Draw();
	void DrawLines();

private:
	//VAO acts like id on gpu
	GLuint m_ID = 0;
	std::vector<GLuint> m_VBOs;
	GLuint m_IBO;
	size_t m_NumIndex;
};

class Model
{
public:
	Model(): m_Meshes() {};
	Model(std::string fileName, std::string mapName,glm::vec3 scale = glm::vec3(1.f));
	Model(std::vector<Mesh> mesh, std::string mapname);
	void Draw();
	void DrawLines();

	std::string GetName() { return name; }
private:
	std::vector<Mesh> m_Meshes;
	std::string name;

};