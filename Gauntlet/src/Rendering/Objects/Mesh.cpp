#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	
	m_NumIndex = indices.size();
	// create vao
	
	unsigned int VAO = 1;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//create a buffer to store the data in GPU memory
	GLuint VBO;
	
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &m_IBO);

	//now bind to the elements buffer for the index's
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	//assign index data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndex * sizeof(GLuint),
		&indices[0], GL_STATIC_DRAW);

	//tell GL which buffer we would like to work with?
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//assign the data to the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		&vertices[0], GL_STATIC_DRAW);
	
	m_VBOs.push_back(VBO);
	

	//tell GL how the data is stored?
	//carefull NULL to use bound buffer or pointer to data not on gpu!!!
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

	//tell GL which attrib we would like to use
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	m_ID = VAO;
}
void Mesh::Draw()
{
	glBindVertexArray(m_ID);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_NumIndex, GL_UNSIGNED_INT, (void*)0);
}
void Mesh::DrawLines()
{
	glBindVertexArray(m_ID);
	glDrawElements(GL_LINE_LOOP, (GLsizei)m_NumIndex, GL_UNSIGNED_INT, (void*)0);
}
Model::Model(std::string fileName, glm::vec3 scale)
	:m_Meshes()
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;
	bool ret = false;
	ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, fileName.c_str());
	//prevent warning
	(void)ret;

	if (!warn.empty()) {
		std::cout << warn << std::endl;
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	for(size_t j = 0; j < shapes.size(); j++)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
	
		for (unsigned int i = 0; i < shapes[j].mesh.indices.size(); i++)
		{
			Vertex v;
			v.position.x = attrib.vertices[3 * shapes[j].mesh.indices[i].vertex_index] * scale.x;
			v.position.y = attrib.vertices[3 * shapes[j].mesh.indices[i].vertex_index + 1] * scale.y;
			v.position.z = attrib.vertices[ 3 * shapes[j].mesh.indices[i].vertex_index + 2] * scale.z;

			//if no normals present
			if (shapes[j].mesh.indices[i].normal_index >= 0)
			{
				v.normal.x = attrib.normals[3 * shapes[j].mesh.indices[i].normal_index];
				v.normal.y = attrib.normals[3 * shapes[j].mesh.indices[i].normal_index + 1];
				v.normal.z = attrib.normals[3 * shapes[j].mesh.indices[i].normal_index + 2];
			}
			else v.normal = glm::vec3(0.f, 0.f, 1.f);
			//if no texturecoords
			if (shapes[j].mesh.indices[i].texcoord_index >= 0)
			{
				v.UV.x = attrib.texcoords[2 * shapes[j].mesh.indices[i].texcoord_index];
				v.UV.y = attrib.texcoords[2 * shapes[j].mesh.indices[i].texcoord_index + 1];
			}
			else v.UV = glm::vec2(0.f, 0.f);

			vertices.push_back(v);
			indices.push_back(i);
		}

		m_Meshes.push_back(Mesh(vertices, indices));
	}
}
Model::Model(std::vector<Mesh> mesh)
{
	m_Meshes = mesh;
}
void Model::Draw()
{
	for(auto &mesh:m_Meshes)
	{
		mesh.Draw();
	}

}
void Model::DrawLines()
{
	for (auto &mesh : m_Meshes)
	{
		mesh.DrawLines();
	}
}