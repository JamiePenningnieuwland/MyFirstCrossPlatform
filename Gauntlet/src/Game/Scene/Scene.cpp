#include "Scene.h"
#include "Engine/Managers/DebugDrawManager.h"
#include "Game/GameObjects/GameObject.h"
#include "Game/Components/Components.h"
#include "Engine/Managers/Loader.h"
#include <fstream>
#include "Core/Application.h"
#include "Engine/MathUtils.h"
#include <thread>

//Serialization and deserialization
//-----------------------------------------------------------------------------------
namespace YAML
{
	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2 rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}
		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;
			rhs.x = node[0].as<float>();
			rhs.x = node[1].as<float>();
			return true;
		}
	};
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3 rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
	template<>
	struct convert<glm::quat>
	{
		static Node encode(const glm::quat rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}
		static bool decode(const Node& node, glm::quat& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
	Emitter& operator << (YAML::Emitter& out, const glm::vec3& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}
	Emitter& operator << (YAML::Emitter& out, const glm::quat& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}
	Emitter& operator << (YAML::Emitter& out, const glm::vec2& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
	return out;
}

}
void Scene::GetModelName(YAML::Emitter& out, std::string sceneName)
{
	std::vector<std::string> names;
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->HasComponent<RenderComponent>())
		{
			auto renderComp = gameObject->GetComponent<RenderComponent>();
			names.push_back(renderComp->model->GetFullDirectory());
		}
		else if (gameObject->HasComponent<AnimationRenderComponent>())
		{
			auto renderComp = gameObject->GetComponent<AnimationRenderComponent>();
			names.push_back(renderComp->model->GetFullDirectory());
	
		}
	}
	//TO delete duplicate names
	std::sort(names.begin(), names.end());
	auto last = std::unique(names.begin(), names.end());
	names.erase(last, names.end());

	for(int i = 0; i < names.size(); i ++)
	{
		out << YAML::BeginMap; //ModelName
		out << YAML::Key << "ModelName" << YAML::Value << names[i];
		out << YAML::Key << "TEST";
		out << YAML::BeginMap;
		out << YAML::Key << "Generated" << YAML::Value << ResourceManager::GetModel(names[i])->GeneratedMesh;
		out << YAML::EndMap;
		out << YAML::EndMap; //ModelName
	}
}
void Scene::Serialize(const std::string& filename, std::string sceneName)
{
	//took reference from the cherno // https://youtu.be/IEiOP7Y-Mbc
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Scene" << YAML::Value << sceneName.c_str();
	
	out << YAML::Key << "Models" << YAML::Value << YAML::BeginSeq;

	GetModelName(out, sceneName);
	
	out << YAML::EndSeq;
	out << YAML::Key << "GameObjects" << YAML::Value << YAML::BeginSeq;

	for (auto& entity : gameObjects)
	{
		SerializeObject(out, entity);
	}
	out << YAML::EndSeq;
	out << YAML::EndMap;

	std::ofstream fout(filename);
	const char* fileString = out.c_str();

	fout << fileString;
}
void Scene::SerializeObject(YAML::Emitter& out, GameObject* gameObject)
{
	out << YAML::BeginMap; //gameObject
	out << YAML::Key << "GameObject";
	out << YAML::Value << gameObject->GetComponent<TagComponent>()->Tag.c_str();

		//transform
		out << YAML::Key << "Transform";
		out << YAML::BeginMap; //transform
		auto transformcomp = gameObject->GetComponent<TransformComponent>();
	
		out << YAML::Key << "Position" << YAML::Value << transformcomp->Position;
		out << YAML::Key << "Rotation" << YAML::Value << transformcomp->Rotation;
		out << YAML::Key << "Scale" << YAML::Value << transformcomp->Scale;
		out << YAML::EndMap; //transform
		
		//cameraComponent
		if(gameObject->HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; //cameracomponent
			auto cameraComp = gameObject->GetComponent<CameraComponent>();
			auto camera = cameraComp->Cam;
			out << YAML::Key << "Fov" << YAML::Value << camera.GetFov();
			out << YAML::Key << "Near" << YAML::Value << camera.GetNear();
			out << YAML::Key << "Far" << YAML::Value << camera.GetFar();
			out << YAML::Key << "AspectRatio" << YAML::Value << camera.GetAspectRatio();

			out << YAML::Key << "IsMain" << YAML::Value << cameraComp->IsMain;
			out << YAML::Key << "Offset" << YAML::Value << cameraComp->Offset;
			out << YAML::Key << "ObjectOffset" << YAML::Value << cameraComp->ObjectPositionOffset;
		
			out << YAML::EndMap; //cameracomponent	
		}
		if(gameObject->HasComponent<CameraControlComponent>())
		{
			out << YAML::Key << "CameraControlComponent";
			out << YAML::BeginMap; //CameraControlComponent
			auto cameraControlComp = gameObject->GetComponent<CameraControlComponent>();
	
			out << YAML::Key << "Distance" << YAML::Value << cameraControlComp->Distance;
			out << YAML::Key << "Rotation" << YAML::Value << cameraControlComp->Rotation;

			out << YAML::EndMap; //CameraControlComponent	
		
		}
		if(gameObject->HasComponent<PlayerControllerComponent>())
		{
			out << YAML::Key << "PlayerControllerComponent";
			out << YAML::BeginMap; //CameraControlComponent
			auto playerControlComp = gameObject->GetComponent<PlayerControllerComponent>();
			out << YAML::Key << "Active" << YAML::Value << playerControlComp->IsActive;
			out << YAML::Key << "Strength" << YAML::Value << playerControlComp->Strength;
			out << YAML::EndMap; //PlayerControllerComponent	

		}
		if (gameObject->HasComponent<PhysicsComponent>())
		{
			out << YAML::Key << "PhysicsComponent";
			out << YAML::BeginMap; //PhysicsComponent
			auto Comp = gameObject->GetComponent<PhysicsComponent>();
			std::string typeName;
			if (Comp->Shape == Geometry::Box)
				typeName = "Box";
			if (Comp->Shape == Geometry::Sphere)
				typeName = "Sphere";
			if (Comp->Shape == Geometry::Capsule)
				typeName = "Capsule";

			out << YAML::Key << "CollisionType" << YAML::Value << typeName;
			out << YAML::Key << "Mass" << YAML::Value << Comp->mass;

			out << YAML::Key << "Offset" << YAML::Value << Comp->Offset;
			out << YAML::Key << "Scale" << YAML::Value << Comp->Scale;
			out << YAML::EndMap; //PhysicsComponent	 
		}
		if(gameObject->HasComponent<RenderComponent>())
		{
			out << YAML::Key << "RenderComponent";
			out << YAML::BeginMap; //RenderComponent
			auto renderComp = gameObject->GetComponent<RenderComponent>();

			out << YAML::Key << "Model";
			out << YAML::BeginMap; //model
			out << YAML::Key << "Model Name" << YAML::Value << renderComp->model->GetFullDirectory();
			out << YAML::EndMap; //model	
			out << YAML::EndMap; //RenderComponent	
		}
		if (gameObject->HasComponent<AnimationRenderComponent>())
		{
			out << YAML::Key << "AnimationRenderComponent";
			out << YAML::BeginMap; //RenderComponent
			auto renderComp = gameObject->GetComponent<AnimationRenderComponent>();

			out << YAML::Key << "Model";
			out << YAML::BeginMap; //model
			out << YAML::Key << "Active" << YAML::Value << renderComp->isPlaying;
			out << YAML::Key << "Model Name" << YAML::Value << renderComp->model->GetFullDirectory();
			out << YAML::EndMap; //model	


			out << YAML::EndMap; //RenderComponent	
		}

	out << YAML::EndMap; //gameObject

}
bool Scene::Deserialize(const std::string& filename)
{
	Unload();

	std::vector<GameObject*> MapTiles = mapload->LoadTiledMap(map1, m_dynamicsWorld, m_dispatcher);
	gameObjects.insert(gameObjects.end(), MapTiles.begin(), MapTiles.end());

	//std::vector<GameObject*> spawners = spawnLoad->LoadSpawners(m_dynamicsWorld, m_dispatcher);
	//gameObjects.insert(gameObjects.end(), spawners.begin(), spawners.end());
	for(int i = 0; i < 10; i++)
		gameObjects.push_back(spawnLoad->LoadSpawner(m_dynamicsWorld, m_dispatcher));


	std::ifstream stream(filename);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str());
	if (!data["Scene"])
		return false;

	std::string sceneName = data["Scene"].as<std::string>();

	auto ModelsMap = data["Models"];
	if(ModelsMap)
	{
		for(auto model: ModelsMap)
		{
			auto  name = model["ModelName"].as<std::string>();
			auto TEST = model["TEST"];
			if(ResourceManager::GetModel(name) == nullptr)
			{
				bool Generated = TEST["Generated"].as<bool>();
				ResourceManager::AddModel(Generated, name);
			}
		}
	}
	
	auto GameObjects = data["GameObjects"];
	if(GameObjects)
	{
		for(auto gameObject:GameObjects)
		{
			auto transformComponent = gameObject["Transform"];
			auto cameraComponent = gameObject["CameraComponent"];
			auto cameraControlComponent = gameObject["CameraControlComponent"];
			auto physicsComponent = gameObject["PhysicsComponent"];
			auto playerControlComponent = gameObject["PlayerControllerComponent"];
			auto renderComponent = gameObject["RenderComponent"];
			auto animationRenderComponent = gameObject["AnimationRenderComponent"];
			auto meshRenderComponent = gameObject["MeshRenderComponent"];

			std::string name = gameObject["GameObject"].as<std::string>();
			GameObject* deserializedObject = new GameObject(name);
			if(transformComponent)
			{
				auto tc = deserializedObject->GetComponent<TransformComponent>();
				tc->Position = transformComponent["Position"].as<glm::vec3>();
				tc->Rotation = transformComponent["Rotation"].as<glm::quat>();
				tc->Scale = transformComponent["Scale"].as<glm::vec3>();
			}
			if(cameraComponent)
			{
				auto cameraComp = deserializedObject->AddComponent<CameraComponent>();
				cameraComp->Cam.SetFov(cameraComponent["Fov"].as<float>());
				cameraComp->Cam.SetNear(cameraComponent["Near"].as<float>());
				cameraComp->Cam.SetFar(cameraComponent["Far"].as<float>());
				cameraComp->Offset = cameraComponent["Offset"].as<glm::vec3>();
				cameraComp->ObjectPositionOffset = cameraComponent["ObjectOffset"].as<glm::vec3>();
				cameraComp->Cam.SetAspectRatio(cameraComponent["AspectRatio"].as<float>());
				cameraComp->IsMain = (cameraComponent["IsMain"].as<bool>());
			}
			if(cameraControlComponent)
			{
				auto camControl = deserializedObject->AddComponent<CameraControlComponent>();
				camControl->Distance = cameraControlComponent["Distance"].as<float>();
				camControl->Rotation = cameraControlComponent["Rotation"].as<glm::vec2>();
			}
			if(physicsComponent)
			{
				//to do add geometry
				Geometry type;
				std::string typeName = physicsComponent["CollisionType"].as<std::string>();
				if (typeName == "Box")
					type = Geometry::Box;
				if (typeName == "Sphere")
					type = Geometry::Sphere;
				if (typeName == "Capsule")
					type = Geometry::Capsule;

				float mass = physicsComponent["Mass"].as<float>();
				auto physComp = deserializedObject->AddComponent<PhysicsComponent>(mass, m_dynamicsWorld, m_dispatcher,type);
				physComp->Offset = physicsComponent["Offset"].as<glm::vec3>();
				physComp->Scale = physicsComponent["Scale"].as<glm::vec3>();
				
			}
			if(playerControlComponent)
			{
				float s = playerControlComponent["Strength"].as<float>();
				deserializedObject->AddComponent<PlayerControllerComponent>(s);
				deserializedObject->GetComponent<PlayerControllerComponent>()->IsActive = playerControlComponent["Active"].as<bool>();
			}
			if(renderComponent)
			{
				Model* model = ResourceManager::GetModel(renderComponent["Model"]["Model Name"].as<std::string>());// &models[renderComponent["Model"]["Model Name"].as<std::string>()];
				deserializedObject->AddComponent<RenderComponent>(model);
		
			}
			if (animationRenderComponent)
			{
				Model* model = ResourceManager::GetModel(animationRenderComponent["Model"]["Model Name"].as<std::string>());// &models[animationRenderComponent["Model"]["Model Name"].as<std::string>()];
		
				deserializedObject->AddComponent<AnimationRenderComponent>(model);
				auto comp  = deserializedObject->GetComponent<AnimationRenderComponent>();
				comp->activeAnimation = comp->model->GetFullDirectory() + "mixamo.com";
			}
			gameObjects.push_back(deserializedObject);
			//deleted.push_back(false);
			//gameObjects[0]->GetComponent<PhysicsComponent>()->simpleColshape = false;
		}
	}
	return true;
}


//-----------------------------------------------------------------------------------

Scene::Scene(btDiscreteDynamicsWorld* dynamicWorld, btCollisionDispatcher* dispatcher)
	: m_Shader("Shader")
	, m_DebugShader(new Shader("debugShader"))
	, m_AnimatedShader("AnimatedShader")
	, m_dispatcher(dispatcher)
{
	m_dynamicsWorld = dynamicWorld;
	bulletDraw = new DebugDrawManager(m_dynamicsWorld, m_DebugShader);
	std::string skycubeFace[6]
	{
		"Resources/Textures/right.jpg",
		"Resources/Textures/left.jpg",
		"Resources/Textures/top.jpg",
		"Resources/Textures/bottom.jpg",
		"Resources/Textures/front.jpg",
		"Resources/Textures/back.jpg"
	};
	/*std::string skycubeFace[6]
	{
		"Resources/Textures/right.png",
		"Resources/Textures/left.png",
		"Resources/Textures/top.png",
		"Resources/Textures/bottom.png",
		"Resources/Textures/front.png",
		"Resources/Textures/back.png"
	};*/
	SkyBoxShader = Shader("cubeShader");
	singeltonSky = new SkyBox(skycubeFace);

};
void Scene::BindShaderToMVP( Shader& shader, glm::mat4 projection, glm::mat4 view)
{
	shader.Bind();
	shader.UploadUniform("projection", projection);
	shader.UploadUniform("view", view);
	shader.UploadUniform("uLightDir", LightDirection);
}
void Scene::Render()
{
	if(gameObjects.size() != 0)
	{
		BindShaderToMVP(m_Shader,m_Cam->GetProjection(),m_Cam->GetView());
		for (auto& gameObject : gameObjects)
		{
			if (gameObject->HasComponent<RenderComponent>())
			{
			
					gameObject->GetComponent<RenderComponent>()->Render(m_Shader);
			
			}
		}
		BindShaderToMVP(m_AnimatedShader, m_Cam->GetProjection(), m_Cam->GetView());


		for (auto& gameObject : gameObjects)
		{
			if (gameObject->HasComponent<AnimationRenderComponent>())
			{
				gameObject->GetComponent<AnimationRenderComponent>()->Render(m_AnimatedShader);
			}
		}
	
		if (enableDebugLines == true)
		{
			BindShaderToMVP(*m_DebugShader, m_Cam->GetProjection(), m_Cam->GetView());
			
			for (auto& gameObject : gameObjects)
			{
				if (gameObject->HasComponent<PhysicsComponent>())
				{
					if(gameObject->GetComponent<TagComponent>()->Tag != "Tile")
						bulletDraw->Draw(gameObject);
				};
			}
		}
	
	}
	
	singeltonSky->Draw(SkyBoxShader, m_Cam->GetView(), m_Cam->GetProjection());

}
void Scene::Update(float deltaTime, btDiscreteDynamicsWorld* dynamicWorld)
{
	
	if (enablePhysics == true)
	{
		dynamicWorld->stepSimulation(deltaTime, 5);
	}
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->HasComponent<PhysicsComponent>())
		{
			gameObject->GetComponent<PhysicsComponent>()->CopyTransformFromPhysicsWorld();
		};
	}
	for (auto& gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->HasComponent<CameraComponent>())
		{
			auto cameraComp = gameObject->GetComponent<CameraComponent>();
			float aspectRatio = static_cast<float>(Application::Get()->GetWin().GetWidth()) /
			static_cast<float>(Application::Get()->GetWin().GetHeight());
			cameraComp->Cam.SetAspectRatio(aspectRatio);
			if (cameraComp->IsMain)
			{
				m_Cam = cameraComp;
				break;
			}
		};
	}
		
}
void Scene::LateUpdate(float deltaTime)
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->HasComponent<PhysicsComponent>())
		{
			gameObject->GetComponent<PhysicsComponent>()->CopyTransform();
		};
	}
}
void Scene::Unload()
{
	for(auto& Entities: gameObjects)
	{
		delete Entities;
	}
	gameObjects.clear();
}
void Scene::AddGameObject(GameObject* object)
{
	gameObjects.push_back(object);
}
void Scene::KeyPressEvent()
{
	
}
