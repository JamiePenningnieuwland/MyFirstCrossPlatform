#include "Game.h"
#include "Input.h"
#include "Game/Components/Components.h"
#include "Core/Application.h"
#include <thread>



void Game::Init()
{
	CreatePhysicsWorld();
	scene = Scene(m_dynamicsWorld, m_dispatcher);
	//state = GameState::LoadingScreen;
}
std::string name_scene;
void Game::Update(float deltaTime)
{
	//UI
	Input::LockMouse(GamePlay);

	switch(state)
	{
	case GameState::Menu:
	{
		GameUI::GameStart(state);
		GamePlay = false;

		firstMenu = true;
		break;
	}
	case GameState::MenuChoice:
	{
		GameUI::MakeChoice(state, mType);
		GamePlay = false;

		break;
	}
	case GameState::LoadingScreen:
	{
		GameUI::LoadingScreen(state, mType, deltaTime);
		scene.Deserialize(name_scene);


		break;
	}
	case GameState::Settings:
	{
		//TODO
		break;
	}
	case GameState::GameMenu:
	{
		GameUI::GameMenu(state, mType, scene);
		GamePlay = false;

		Menu = false;
		break;
	}
	case GameState::Level:
	{
		if (firstMenu)
		{
			name_scene = "Resources/Scenes/CharacterControl.Scene";
			scene.LateUpdate(deltaTime);
			scene.Update(deltaTime, m_dynamicsWorld);
			state = GameState::LoadingScreen;
			//scene.Deserialize("Resources/Scenes/CharacterControl.Scene");
			firstMenu = false;
			
		}
		else
		{
			if (Menu)
				state = GameState::GameMenu;
			GameUI::GameMenu(state, mType, scene);

			//updates
			scene.Update(deltaTime, m_dynamicsWorld);
			scene.LateUpdate(deltaTime);

			//Rendering
			scene.Render();
		}
		ProcessInput(deltaTime);
		break;
	}
	case GameState::Debug:
	{
		if (firstMenu)
		{
			scene.LateUpdate(deltaTime);
			scene.Update(deltaTime, m_dynamicsWorld);
			name_scene = "Resources/Scenes/CharacterControl.Scene";
			state = GameState::LoadingScreen;

			firstMenu = false;
		}
		else
		{
			if (Menu)
				state = GameState::GameMenu;

			scene.Update(deltaTime, m_dynamicsWorld);
			if(Controls)
			{
					GamePlay = false;
				Control.DebugControlWindow(scene, deltaTime);
			}
			//updates
			scene.LateUpdate(deltaTime);
			//Rendering
			scene.Render();
		}
		ProcessInput(deltaTime);
		break;
	}
	case GameState::SaveMenu:
	{
		GameUI::SaveMenu(state,scene, mType);
		break;
	}
	}
}
void Game::KeyPressEvent(int key)
{
	if (key == KEY_ESCAPE)
	{
		Menu = !Menu;
	}
	if(key == KEY_TAB)
	{
		Controls = !Controls;
	}
}
void Game::ProcessInput(float deltaTime)
{
	if (state == GameState::Level || !Controls)
	{
		GamePlay = true;
	}
	if (state == GameState::Debug)
		Input::HoldMouseInput(Controls);
	else Input::HoldMouseInput(false);
}
void Game::Shutdown()
{

}
void Game::CreatePhysicsWorld()
{
	//bullet
	btBroadphaseInterface* broadphase;
	btCollisionDispatcher* dispatcher;
	btConstraintSolver* solver;
	btDefaultCollisionConfiguration* collisionConfiguration;

	///collision configuration contains default setup for memory, collision setup
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new btCollisionDispatcher(collisionConfiguration);
	broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	solver = sol;
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, broadphase, solver, collisionConfiguration);
	m_dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

}
void SkyBox::Draw(Shader shader, glm::mat4 view, glm::mat4 projection)
{
	//learnopengl////////////
	glDepthFunc(GL_LEQUAL);  
	shader.Bind();
	glm::mat4 NewView;
	NewView = glm::mat4(glm::mat3(view));
	shader.UploadUniform("view", NewView);
	shader.UploadUniform("projection", projection);

	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}