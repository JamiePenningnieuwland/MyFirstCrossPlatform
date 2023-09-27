#pragma once
#include "Engine/Rendering/Shaders/Shader.h"
#include <vector>
#include "Game/Scene/Scene.h"

#pragma warning(push, 0)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)

#include "UI/UI.h"
#include "UI/DebugUI.h"
#include <Game/GameObjects/GameObject.h>

class Model;
class Texture;

class Game
{
public:
	Game() 
		: Control()
	{};

	void Init();
	void Update(float deltaTime);
	void Shutdown();
	void KeyPressEvent(int key);
	bool loadScene();
	void ButtonPressEvent(int button)
	{
	}

private:

	Scene scene;
	void CreatePhysicsWorld();
	void ProcessInput(float deltaTime);
	DebugUI Control;
	GameState state = GameState::Menu;
	CharacterType mType = CharacterType::Hunter;

	bool GamePlay = false;
	bool Controls = false;
	
	bool enablePhysics = false;
	bool enableDebugLines = false;

	bool firstMenu = true;
	bool Menu = false;

	glm::vec3 LightDirection = { 0.2f, -0.8f, -0.4f };

	//bullet

	btCollisionDispatcher* m_dispatcher;
	btDiscreteDynamicsWorld* m_dynamicsWorld;

	char saveSceneFile[128] = "";
	char loadSceneFile[128] = "";
	

};