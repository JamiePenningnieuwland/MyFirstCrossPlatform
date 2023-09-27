#pragma once
#include <vector>

#include "Engine/Rendering/Shaders/Shader.h"
#include "Engine/Rendering/Models/Model.h"


#pragma warning(push, 0)
#include <yaml-cpp/yaml.h>
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)

class GameObject;
class Shader;
class Texture;
class CameraComponent;
class DebugDrawManager;
class MapLoader;
class SpawnLoaders;
class SkyBox;
class Scene
{
public:
	Scene() = default;
	Scene(btDiscreteDynamicsWorld* dynamicWorld, btCollisionDispatcher* dispatcher);
	void KeyPressEvent();
	void LateUpdate(float deltaTime);
	void AddGameObject(GameObject* Obj);
	void Unload();
	void Update(float deltaTime, btDiscreteDynamicsWorld*);
	std::vector<GameObject*>& GetSceneObjectsArray() { return gameObjects; };
	void Render();
	btDiscreteDynamicsWorld* GetDynamicWorld() { return m_dynamicsWorld; }
	btCollisionDispatcher* GetCollisionDispatcher() { return m_dispatcher; }
	//--------------------------------------------------------------

	void SerializeObject(YAML::Emitter& emmiter, GameObject*);
	void Serialize(const std::string& filename,std::string sceneName);
	bool Deserialize(const std::string& filename);
	//--------------------------------------------------------------

	bool enableDebugLines = false;
	bool enablePhysics = true;
	std::vector<GameObject*> gameObjects;

private:
	void BindShaderToMVP(Shader& shader, glm::mat4 projection, glm::mat4 view);
	void GetModelName(YAML::Emitter& out, std::string sceneName);

	CameraComponent* m_Cam;
	DebugDrawManager* bulletDraw;
	MapLoader* mapload;
	SpawnLoaders* spawnLoad;
	
	//skybox
	SkyBox* singeltonSky;
	Shader SkyBoxShader;

	Shader m_Shader;
	Shader* m_DebugShader;
	Shader m_AnimatedShader;

	glm::vec3 LightDirection = { 0.2f, -0.8f, -0.4f };

	btDiscreteDynamicsWorld* m_dynamicsWorld;
	btCollisionDispatcher* m_dispatcher;
	int map1[1024]
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0,
		0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	};
	
	glm::vec3 tiles[256]
	{
		{1.,1.,1.  },{1.,2.,1.  },    {2.,0.,1. },{3.,0.,1. },{4.,0.,1. },{5.,0.,1. },{6.,0.,1. }, {7.,0.,1. },{8.,0.,1. },{9.,0.,1. },{10.,0.,1. },{11.,0.,1. },{12.,0.,1. },		{12.,1.,1. },{12.,2.,1. },
		{1.,1.,2.  },{1.,2.,2.  },    {2.,0.,2. },{3.,0.,2. },{4.,0.,2. },{5.,0.,2. },{6.,0.,2. }, {7.,0.,2. },{8.,0.,2. },{9.,0.,2. },{10.,0.,2. },{11.,0.,2. },{12.,0.,2. },		{12.,1.,2. },{12.,2.,2. },
		{1.,1.,3.  },{1.,2.,3.  },    {2.,0.,3. },{3.,0.,3. },{4.,0.,3. },{5.,0.,3. },{6.,0.,3. }, {7.,0.,3. },{8.,0.,3. },{9.,0.,3. },{10.,0.,3. },{11.,0.,3. },{12.,0.,3. },		{12.,1.,3. },{12.,2.,3. },
		{1.,1.,4.  },{1.,2.,4.  },    {2.,0.,4. },{3.,0.,4. },{4.,0.,4. },{5.,0.,4. },{6.,0.,4. }, {7.,0.,4. },{8.,0.,4. },{9.,0.,4. },{10.,0.,4. },{11.,0.,4. },{12.,0.,4. },		{12.,1.,4. },{12.,2.,4. },
		{1.,1.,5.  },{1.,2.,5.  },    {2.,0.,5. },{3.,0.,5. },{4.,0.,5. },{5.,0.,5. },{6.,0.,5. }, {7.,0.,5. },{8.,0.,5. },{9.,0.,5. },{10.,0.,5. },{11.,0.,5. },{12.,0.,5. },		{12.,1.,5. },{12.,2.,5. },
		{1.,1.,6.  },{1.,2.,6.  },    {2.,0.,6. },{3.,0.,6. },{4.,0.,6. },{5.,0.,6. },{6.,0.,6. }, {7.,0.,6. },{8.,0.,6. },{9.,0.,6. },{10.,0.,6. },{11.,0.,6. },{12.,0.,6. },		{12.,1.,6. },{12.,2.,6. },
		{1.,1.,7.  },{1.,2.,7.  },    {2.,0.,7. },{3.,0.,7. },{4.,0.,7. },{5.,0.,7. },{6.,0.,7. }, {7.,0.,7. },{8.,0.,7. },{9.,0.,7. },{10.,0.,7. },{11.,0.,7. },{12.,0.,7. },		{12.,1.,7. },{12.,2.,7. },
		{1.,1.,8.  },{1.,2.,8.  },    {2.,0.,8. },{3.,0.,8. },{4.,0.,8. },{5.,0.,8. },{6.,0.,8. }, {7.,0.,8. },{8.,0.,8. },{9.,0.,8. },{10.,0.,8. },{11.,0.,8. },{12.,0.,8. },		{12.,1.,8. },{12.,2.,8. },
		{1.,1.,9.  },{1.,2.,9.  },    {2.,0.,9. },{3.,0.,9. },{4.,0.,9. },{5.,0.,9. },{6.,0.,9. }, {7.,0.,9. },{8.,0.,9. },{9.,0.,9. },{10.,0.,9. },{11.,0.,9. },{12.,0.,9. },		{12.,1.,9. },{12.,2.,9. },
		{1.,1.,10. },{1.,2.,10. },    {2.,0.,10.},{3.,0.,10.},{4.,0.,10.},{5.,0.,10.},{6.,0.,10.}, {7.,0.,10.},{8.,0.,10.},{9.,0.,10.},{10.,0.,10.},{11.,0.,10.},{12.,0.,10.},		{12.,1.,10.},{12.,2.,10.},
		{1.,1.,11. },{1.,2.,11. },    {2.,0.,11.},{3.,0.,11.},{4.,0.,11.},{5.,0.,11.},{6.,0.,11.}, {7.,0.,11.},{8.,0.,11.},{9.,0.,11.},{10.,0.,11.},{11.,0.,11.},{12.,0.,11.},		{12.,1.,11.},{12.,2.,11.},
		{1.,1.,12. },{1.,2.,12. },    {2.,0.,12.},{3.,0.,12.},{4.,0.,12.},{5.,0.,12.},{6.,0.,12.}, {7.,0.,12.},{8.,0.,12.},{9.,0.,12.},{10.,0.,12.},{11.,0.,12.},{12.,0.,12.},		{12.,1.,12.},{12.,2.,12.},
		{1.,1.,13. },{1.,2.,13. },    {2.,0.,13.},{3.,0.,13.},{4.,0.,13.},{5.,0.,13.},{6.,0.,13.}, {7.,0.,13.},{8.,0.,13.},{9.,0.,13.},{10.,0.,13.},{11.,0.,13.},{12.,0.,13.},		{12.,1.,13.},{12.,2.,13.},
		{1.,1.,14. },{1.,2.,14. },    {2.,0.,14.},{3.,0.,14.},{4.,0.,14.},{5.,0.,14.},{6.,0.,14.}, {7.,0.,14.},{8.,0.,14.},{9.,0.,14.},{10.,0.,14.},{11.,0.,14.},{12.,0.,14.},		{12.,1.,14.},{12.,2.,14.},
		{1.,1.,15. },{1.,2.,15. },    {2.,0.,15.},{3.,0.,15.},{4.,0.,15.},{5.,0.,15.},{6.,0.,15.}, {7.,0.,15.},{8.,0.,15.},{9.,0.,15.},{10.,0.,15.},{11.,0.,15.},{12.,0.,15.},		{12.,1.,15.},{12.,2.,15.},
		{1.,1.,16. },{1.,2.,16. },    {2.,0.,16.},{3.,0.,16.},{4.,0.,16.},{5.,0.,16.},{6.,0.,16.}, {7.,0.,16.},{8.,0.,16.},{9.,0.,16.},{10.,0.,16.},{11.,0.,16.},{12.,0.,16.},		{12.,1.,16.},{12.,2.,16.},
		
	};

};
const float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

//Mostly taken from opengl
class SkyBox
{
public:
	SkyBox() = default;
	SkyBox(std::string cubefaces[6])
	{
		// skybox VAO
		unsigned int skyboxVBO;
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		loadCubemap(cubefaces);
	}
	void Draw(Shader shader, glm::mat4 view, glm::mat4 projection);
	void loadCubemap(std::string faces[])
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < 6; i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		cubemapTexture = textureID;
	}
private:
	unsigned int skyboxVAO;
	unsigned int cubemapTexture;


};