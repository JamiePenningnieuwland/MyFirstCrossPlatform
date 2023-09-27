#include "DebugUI.h"
#include "Game/GameObjects/GameObject.h"
#include "Game/Components/Components.h"
#include "Engine/MathUtils.h"
#include "Game/Scene/Scene.h"
#include <imgui.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>


namespace Objects
{
	void CreateObject(std::string name, Scene& scene);
	void DeleteObject(GameObject* object, Scene& scene);
}
void Objects::CreateObject(std::string name, Scene& scene)
{
	GameObject* obj = new GameObject(name);
	scene.gameObjects.push_back(obj);

}
void Objects::DeleteObject(GameObject* object, Scene& scene)
{
	auto test = std::remove(scene.gameObjects.begin(), scene.gameObjects.end(), object);
	scene.gameObjects.erase(test, scene.gameObjects.end());
	delete object;

}
void DebugUI::DebugControlWindow(Scene& scene, float deltaTime)
{
	ImGui::Begin("Controls");
	if (ImGui::TreeNode("Scene"))
	{
		std::string ifNoName = "Untitled";

		ImGui::PushID("save file");
		ImGui::InputTextWithHint(" ", "filename", saveSceneFile, 128);
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			std::string name1 = saveSceneFile;
			if (name1.empty())
				name1 = ifNoName;

			std::string output = "Resources/Scenes/" + name1 + ".Scene";
		
			scene.Serialize(output, name1);
		}
		ImGui::PopID();

		ImGui::PushID("load file");
		ImGui::InputTextWithHint(" ", "filename", loadSceneFile, 128);
		ImGui::SameLine();
		if (ImGui::Button("Load"))
		{
			std::string name1 = loadSceneFile;
			if (!name1.empty())
			{
				std::string output = "Resources/Scenes/" + name1 + ".Scene";
				scene.Deserialize(output);
				scene.LateUpdate(deltaTime);
				scene.Update(deltaTime, scene.GetDynamicWorld());
			}
			else printf("no filename selected");
		}
		ImGui::PopID();
		ImGui::TreePop();
	}
	ImGui::Separator();

	if (ImGui::TreeNode("Physics"))
	{
		ImGui::Checkbox("Enable Physics", &scene.enablePhysics);
		ImGui::Checkbox("Enable DebugLines", &scene.enableDebugLines);
		ImGui::TreePop();
	}
	ImGui::Separator();
	if (ImGui::TreeNode("GameObjects"))
	{
		ImGui::InputTextWithHint(" ", "name", Objectname, 128);
		ImGui::SameLine();
		if (ImGui::Button("Add GameObject"))
		{
			std::string name = Objectname;
			if (name.empty())
				name = MathUtils::GenerateRandomName();
			
			Objects::CreateObject(name, scene);
		}
		int i = 0;
		int j = 0;
		for (auto& gameObject :scene.gameObjects)
		{
						
			if (gameObject->GetComponent<TagComponent>()->Tag != "Tile")
			{
				ImGui::PushID(j);
				
				if (ImGui::TreeNode(("Name : " + gameObject->GetComponent<TagComponent>()->Tag).c_str()))
				{
			
					DebugUiTransform(gameObject);
					if(!gameObject->HasComponent<AnimationRenderComponent>())
					{
						ImGui::PushID("Static");
						if (!DebugUiRender(gameObject))
						{
							addDebugUiRender(gameObject);
						}
						ImGui::PopID();
					}
					if(!gameObject->HasComponent<RenderComponent>())
					{
						ImGui::PushID("animated");
						if (!DebugUiAnimatedRender(gameObject))
						{
							addDebugUiAnimatedRender(gameObject);
						}
						ImGui::PopID();
					}
			
					if(!DebugUiPhysics(gameObject))
					{
						addDebugUiPhysics(gameObject,scene);
					}
			
					if (!DebugUiCamera(gameObject))
					{
						addDebugUiCamera(gameObject);
					}
					if (!DebugUiCameraControl(gameObject))
					{
						addDebugUiCameraControl(gameObject);
					}
			
					ImGui::TreePop();
				}
				ImGui::SameLine();
							
				if (ImGui::Button("Delete object"))
				{
					Objects::DeleteObject(gameObject, scene);
					j = 0;
				}
				
				ImGui::PopID();
				j++;
			}
		}
		i++;
		ImGui::TreePop();
	}
	ImGui::End();
}

void DebugUI::DebugUiTransform(GameObject* gameObject)
{
	auto transform = gameObject->GetComponent<TransformComponent>();
	if (ImGui::TreeNode("Transform"))
	{
		if (ImGui::TreeNodeEx("Translation", ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::DragFloat3("", glm::value_ptr(transform->Position), 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Rotation", ImGuiTreeNodeFlags_Leaf))
		{
			glm::vec3 rotation = glm::eulerAngles(transform->Rotation);
			ImGui::DragFloat3("", glm::value_ptr(rotation), 0.01f);
			transform->Rotation = glm::quat(rotation);
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Scale", ImGuiTreeNodeFlags_Leaf))
		{
			ImGui::DragFloat3("", glm::value_ptr(transform->Scale), 0.01f, 0.01f);
			ImGui::TreePop();
		}
		ImGui::TreePop();

	}
}
bool DebugUI::DebugUiRender(GameObject* gameObject)
{
	if (gameObject->HasComponent<RenderComponent>())
	{
		if (ImGui::TreeNode("RenderComponent"))
		{
			auto render = gameObject->GetComponent<RenderComponent>();
			ImGui::Text(render->model->GetFullDirectory().c_str());
			ImGui::TreePop();
		}
		return true;
	}
	return false;
}
bool DebugUI::DebugUiAnimatedRender(GameObject* gameObject)
{
	if (gameObject->HasComponent<AnimationRenderComponent>())
	{
		if (ImGui::TreeNode("AnimationRenderComponent"))
		{
			auto render = gameObject->GetComponent<AnimationRenderComponent>();
			ImGui::Text(render->model->GetFullDirectory().c_str());
			ImGui::DragFloat("AnimationTime", &render->AnimationTime, 0.1f);

			const char** items = new const char* [ResourceManager::GetAnimationMap().size()];
			int itemCurrentIndex = 0;
			int index = 0;

			for (auto& [key, value] : ResourceManager::GetAnimationMap())
			{
				items[index] = key.c_str();
				if (key == render->activeAnimation)
					itemCurrentIndex = index;

				index++;
			}

			if (ImGui::BeginCombo("Animation", items[itemCurrentIndex]))
			{
				for (int id = 0; id < ResourceManager::GetAnimationMap().size(); id++)
				{
					const bool is_selected = (itemCurrentIndex == id);
					if (ImGui::Selectable(items[id], is_selected))
						render->activeAnimation = items[id];

					if (is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::Separator();
			ImGui::TreePop();
		}
		return true;
	}
	return false;
}
bool DebugUI::DebugUiPhysics(GameObject* gameObject)
{
	if (gameObject->HasComponent<PhysicsComponent>())
	{
		if (ImGui::TreeNode("PhysicsComponent"))
		{
			ImGui::Text("Collision shape");
			auto comp = gameObject->GetComponent<PhysicsComponent>();
			std::string shape;
			switch (comp->Shape)
			{
			case Geometry::Box:
			{
				shape = "Box";
				ImGui::Text(shape.c_str());
				if (ImGui::TreeNodeEx("Scale", ImGuiTreeNodeFlags_Leaf))
				{
					ImGui::DragFloat3("", glm::value_ptr(comp->Scale), 0.01f, 0.01f);
					ImGui::TreePop();
				}
				break;
			}
			case Geometry::Capsule:
			{
				shape = "Capsule";
				ImGui::Text(shape.c_str());
				if (ImGui::TreeNodeEx("Scale", ImGuiTreeNodeFlags_Leaf))
				{
					float height = comp->Scale.y;
					float radius = comp->Scale.x / 2.f;
					ImGui::DragFloat("Height", &height, 0.01f, 0.01f);
					ImGui::DragFloat("Radius", &radius, 0.01f, 0.01f);
					comp->Scale.y = height;
					comp->Scale.x = radius * 2;
					ImGui::TreePop();
				}
				//add radius dragfloat

				break;
			}
			case Geometry::Sphere:
			{
				shape = "Sphere";
				ImGui::Text(shape.c_str());
				//add radius dragfloat

				break;
			}
			default:
				break;
			}
			if (ImGui::TreeNodeEx("Offset", ImGuiTreeNodeFlags_Leaf))
			{
				ImGui::DragFloat3("", glm::value_ptr(comp->Offset), 0.01f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNodeEx("Lock Rotations", ImGuiTreeNodeFlags_Leaf))
			{
				ImGui::PushID("x");
				ImGui::Text("X");
				ImGui::SameLine();
				ImGui::Checkbox("", &comp->LockXRotation);
				ImGui::PopID();

				ImGui::SameLine();

				ImGui::PushID("y");
				ImGui::Text("Y");
				ImGui::SameLine();
				ImGui::Checkbox("", &comp->LockYRotation);
				ImGui::PopID();

				ImGui::SameLine();

				ImGui::PushID("Z");
				ImGui::Text("Z");
				ImGui::SameLine();
				ImGui::Checkbox("", &comp->LockZRotation);
				ImGui::PopID();

				ImGui::TreePop();
			}
			ImGui::TreePop();

			if (!DebugUiControls(gameObject))
				addDebugUiControls(gameObject);

			ImGui::Separator();
		}

		return true;
	}
	return false;
}
bool DebugUI::DebugUiControls(GameObject* gameObject)
{
	if (gameObject->HasComponent<PlayerControllerComponent>())
	{
		if (ImGui::TreeNode("ControlComponent"))
		{
			auto ControlComponent = gameObject->GetComponent<PlayerControllerComponent>();

			if (ImGui::TreeNodeEx("Force strength", ImGuiTreeNodeFlags_Leaf))
			{
				ImGui::PushID("s");
				ImGui::DragFloat("", &ControlComponent->Strength, 0.01f, 0.f);
				ImGui::PopID();
				ImGui::TreePop();
			}
			ImGui::Checkbox("Active", &ControlComponent->IsActive);
			ImGui::TreePop();
		}
		return true;
	}
	return false;
}
bool DebugUI::DebugUiCamera(GameObject* gameObject)
{
	if (gameObject->HasComponent<CameraComponent>())
	{
		if (ImGui::TreeNode("CameraComponent"))
		{
			auto cameraComponent = gameObject->GetComponent<CameraComponent>();
			if (ImGui::TreeNodeEx("Offset", ImGuiTreeNodeFlags_Leaf))
			{
				ImGui::DragFloat3("", glm::value_ptr(cameraComponent->Offset), 0.01f, 0.f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNodeEx("Object focus Point", ImGuiTreeNodeFlags_Leaf))
			{
				ImGui::DragFloat3("", glm::value_ptr(cameraComponent->ObjectPositionOffset), 0.01f, 0.f);
				ImGui::TreePop();
			}
			ImGui::Checkbox("Main Camera", &cameraComponent->IsMain);
			ImGui::TreePop();
		}
		return true;
	}
	return false;
}
bool DebugUI::DebugUiCameraControl(GameObject* gameObject)
{
	if (gameObject->HasComponent<CameraControlComponent>())
	{
		if (ImGui::TreeNode("CameraControlComponent"))
		{
			auto cameraControl = gameObject->GetComponent<CameraControlComponent>();

			ImGui::PushID("distance");
			ImGui::DragFloat("", &cameraControl->Distance, 0.01f, 0.f);
			ImGui::PopID();
			ImGui::TreePop();
		}
		return true;
	}
	return false;
}
void DebugUI::addDebugUiRender(GameObject* gameObject)
{
	ImGui::PushID("model");
	if(generated == true)
	{
		ImGui::InputTextWithHint(" ", "texture Filepath", ModelFileName, 128);

	}
	else
	{

		ImGui::InputTextWithHint(" ", "Model Filepath", ModelFileName, 128);
	}
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::Checkbox("Generated", &generated);
	if (ImGui::Button("Add RenderComponent"))
	{
		std::string ModelName = ModelFileName;

		if (ModelName.empty())
		{
			ModelName = "Resources/Models/default.obj";
		}
		if (ResourceManager::GetModel(ModelName) == nullptr/*models.find(ModelName) == models.end()*/)
		{
			//if(ModelName.starts_with("Resources/Textures"))
			/*if (ModelName == "Resources/Textures/Texture.jpg")
			{
				generated = true;
			}*/
			ResourceManager::AddModel(generated, ModelName);

		}
		gameObject->AddComponent<RenderComponent>(ResourceManager::GetModel(ModelName));

	}
	ImGui::Separator();
}
void DebugUI::addDebugUiAnimatedRender(GameObject* gameObject)
{
	ImGui::PushID("animodel");
	ImGui::InputTextWithHint(" ", "Model File name", aModelFileName, 128);
	ImGui::PopID();

	if (ImGui::Button("Add AnimationRenderComponent"))
	{

		std::string ModelName = aModelFileName;

		if (ModelName.empty())
		{
			ModelName = "Resources/Models/default.obj";
		}
		if (ResourceManager::GetModel(ModelName) == nullptr/*models.find(ModelName) == models.end()*/)
		{
			bool generated = false;
			if (ModelName == "Resources/Textures/Texture.jpg")
			{
				generated = true;
			}
			ResourceManager::AddModel(generated, ModelName);
			//models[ModelName] = Model(ModelName.c_str());
		}
		gameObject->AddComponent<AnimationRenderComponent>(ResourceManager::GetModel(ModelName));
	}
}
void DebugUI::addDebugUiPhysics(GameObject* gameObject, Scene& scene)
{

	float mass = 0;
	const char** items = new const char* [4];
	static int itemCurrentIndex = 0;
	items[0] = "Empty";
	items[1] = "Box";
	items[2] = "Sphere";
	items[3] = "Capsule";

	if (ImGui::BeginCombo("Collision Shape", items[itemCurrentIndex]))
	{
		for (int id = 0; id < 4; id++)
		{
			const bool is_selected = (itemCurrentIndex == id);
			if (ImGui::Selectable(items[id], is_selected))
			{
				itemCurrentIndex = id;
			}

			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	if (ImGui::Button("Add PhysicsComponent"))
	{
		Geometry type;// = Geometry::Box;
		if (itemCurrentIndex == 1)
			type = Geometry::Box;
		else if (itemCurrentIndex == 2)
			type = Geometry::Sphere;
		else if (itemCurrentIndex == 3)
			type = Geometry::Capsule;
		if (isDynamic == true)
			mass = 1.f;
		gameObject->AddComponent<PhysicsComponent>(mass, scene.GetDynamicWorld(), scene.GetCollisionDispatcher(), type);


	}
	ImGui::SameLine();
	ImGui::Checkbox("dynamic", &isDynamic);

}
void DebugUI::addDebugUiControls(GameObject* gameObject)
{
	if (ImGui::Button("Add PlayerControllerComponent"))
	{
		gameObject->AddComponent<PlayerControllerComponent>(1.f);
	}
}
void DebugUI::addDebugUiCamera(GameObject* gameObject)
{
	if (ImGui::Button("Add CameraComponent"))
	{
		gameObject->AddComponent<CameraComponent>();
	}
}
void DebugUI::addDebugUiCameraControl(GameObject* gameObject)
{
	if (ImGui::Button("Add CameraControlComponent"))
	{
		gameObject->AddComponent<CameraControlComponent>();
	}
}