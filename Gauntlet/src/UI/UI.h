#pragma once

// save diagnostic state
#pragma warning(push, 0)
#include <imgui.h>
#pragma warning(pop)

enum class GameState
{
	Menu = 0,
	GameMenu = 1,
	Level = 2,
	Debug = 3,
	MenuChoice = 4,
	Settings = 5,
	SaveMenu = 6,
	LoadingScreen = 7,

};
enum class CharacterType
{
	Wizard = 0,
	Hunter = 1,
	Warior = 2,
	Elf = 3,
	Debug = 4,

};

class Scene;
namespace GameUI
{
	void Init();
	void GameMenu(GameState& state, CharacterType& type, Scene& scene);
	void LoadingScreen(GameState& state, CharacterType,float deltaTime);
	void SaveMenu(GameState& state, Scene& scene, CharacterType& type);
	void MakeChoice(GameState& state, CharacterType& type );
	void GameStart(GameState& state);
	void GameEnd();
}

