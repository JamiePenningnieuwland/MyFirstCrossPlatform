#include "UI.h"

#include <string>
#include <Core/Application.h>
#include "Game/Scene/Scene.h"

namespace UIinfo
{
	ImGuiIO io;
	ImFont* boldFont;
	std::string currentGameSlot;
	float time = 0;

	char SaveSlot1[128] = "";
	char SaveSlot2[128] = "";
	char SaveSlot3[128] = "";
	bool SaveSlot1Used[3] = { false };
	bool Saved = false;
	bool done = false;
};

void GameUI::Init()
{
	UIinfo::io = ImGui::GetIO();
}
bool CreateButtonMiddle( std::string name, ImVec2 buttonsize, unsigned int Index, const ImGuiViewport* viewport)
{
	ImGui::SetCursorPos(ImVec2((viewport->Size.x * 0.5f) - buttonsize.x * 0.5f, 
		(viewport->Size.y) - (buttonsize.y  * 1.5f * static_cast<float>(Index))));

	return ImGui::Button(name.c_str(), buttonsize);
}
bool CreateButtonCharacter(CharacterType type, std::string name, ImVec2 size, ImVec2 position)
{
	ImGui::SetCursorPos(position);
	bool returnbool = ImGui::Button(name.c_str(), size);
	if (type == CharacterType::Wizard)
	{
		ImGui::SetCursorPos(ImVec2(position.x, position.y + size.y * 1.1f));
		ImGui::Text("HP:      900 \nSpeed:   ++\nDamage:  ++\nHealing: +++");
	}
	if (type == CharacterType::Elf)
	{
		ImGui::SetCursorPos(ImVec2(position.x, position.y + size.y * 1.1f));
		ImGui::Text("HP:      800 \nSpeed:   +++\nDamage:  +\nHealing: +++");
	}
	if (type == CharacterType::Hunter)
	{
		ImGui::SetCursorPos(ImVec2(position.x, position.y + size.y * 1.1f));
		ImGui::Text("HP:      1000\nSpeed:   +++\nDamage:  ++\nHealing: +");

	}
	if (type == CharacterType::Warior)
	{
		ImGui::SetCursorPos(ImVec2(position.x, position.y + size.y * 1.1f));
		ImGui::Text("HP:      1400\nSpeed:   +\nDamage:  +++\nHealing: +");

	}
	return returnbool;
}
void GameUI::GameMenu(GameState& state, CharacterType& type, Scene& scene) 
{
	bool open = (state == GameState::GameMenu);
	if(open)
	{
		ImGui::GetIO().WantCaptureKeyboard = true;
		static bool use_work_area = true;
		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
		ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
		ImGui::SetNextWindowBgAlpha(1.f);
		ImVec2 buttonSize = ImVec2(200, 50);
		if (ImGui::Begin("Example: Fullscreen window", &open, flags))
		{
			//ImGui::PushFont(UIinfo::boldFont);

			if (CreateButtonMiddle("Resume", buttonSize, 7, viewport))
			{
				UIinfo::Saved = false;
				if (type == CharacterType::Debug)
						state = GameState::Debug;

				else state = GameState::Level;
				open = false;
			}
			if (CreateButtonMiddle("Save game", buttonSize, 6, viewport))
			{
				scene.Serialize("Resources/PlayerData/" + UIinfo::currentGameSlot + ".Scene", UIinfo::currentGameSlot);
				UIinfo::Saved = true;
			}
			if(UIinfo::Saved)
				ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "GAME SAVED");

			if (CreateButtonMiddle("Main Menu", buttonSize, 5, viewport))
			{
				//type = -2;
				UIinfo::Saved = false;
				state = GameState::Menu;
				open = false;
				//startmenu = true;
			}
			if (CreateButtonMiddle("Exit App", buttonSize, 4, viewport))
			{
				UIinfo::Saved = false;
				Application::Get()->WindowOpen = true;
			}
		
			//ImGui::PopFont();
		}
		ImGui::End();
	}
	
}
void GameUI::LoadingScreen(GameState& state, CharacterType type, float deltaTime)
{
	bool open = (state == GameState::LoadingScreen);
	if (open)
	{
	
		ImGui::GetIO().WantCaptureKeyboard = true;
		static bool use_work_area = true;

		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
		ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
		ImGui::SetNextWindowBgAlpha(1.f);
		if (UIinfo::done)
		{
			if (type == CharacterType::Debug)
				state = GameState::Debug;

			else state = GameState::Level;
			
			UIinfo::done = false;
			open = false;
		}
		if (ImGui::Begin("Example: Fullscreen window", &open, flags))
		{
			
			ImGui::SetCursorPos(ImVec2(viewport->GetCenter().x - 30.f, viewport->GetCenter().y));
			if(UIinfo::time > 1.f)
			{
				ImGui::Text("L");  //1
			}
			ImGui::SameLine();
			if (UIinfo::time > 2)
				ImGui::Text("O");  //2
			ImGui::SameLine(); 
			if (UIinfo::time > 3)
				ImGui::Text("A");  //3
			ImGui::SameLine();
			if (UIinfo::time > 4)
				ImGui::Text("D");  //4
			ImGui::SameLine();
			if (UIinfo::time > 5)
				ImGui::Text("I");  //5
			ImGui::SameLine();
			if (UIinfo::time > 6)
				ImGui::Text("N");  //6
			ImGui::SameLine(); 
			if (UIinfo::time > 7)
				ImGui::Text("G");  //7
			ImGui::SameLine(); 
			if (UIinfo::time > 8)
				ImGui::Text(".");  //8
			ImGui::SameLine();
			if (UIinfo::time > 9)
				ImGui::Text(".");  //9
			
			ImGui::SetCursorPos(ImVec2(viewport->GetCenter().x, viewport->GetCenter().y + 30.f));
			if (UIinfo::time > 1.f && UIinfo::time  < 2.f)
				ImGui::Text("10 %");  //1
			if (UIinfo::time > 2.f && UIinfo::time < 3.f)
				ImGui::Text("20 %");  //2
			if (UIinfo::time > 3 && UIinfo::time < 4.f)
				ImGui::Text("30 %");  //3
			if (UIinfo::time > 4 && UIinfo::time < 5.f)
				ImGui::Text("40 %");  //4
			if (UIinfo::time > 5 && UIinfo::time < 6.f)
				ImGui::Text("50 %");  //5
			if (UIinfo::time > 6 && UIinfo::time < 7.f)
				ImGui::Text("60 %");  //6
			if (UIinfo::time > 7 && UIinfo::time < 8.f)
				ImGui::Text("70 %");  //7
			if (UIinfo::time > 8 && UIinfo::time < 9.f)
				ImGui::Text("80 %");  //8
			if (UIinfo::time > 9 && UIinfo::time < 10.f)
				ImGui::Text("90 %");  //9
			if (UIinfo::time > 10)
			{
				ImGui::Text("100 %");  //10
				if (UIinfo::time > 12)
				{
					UIinfo::done = true;
					UIinfo::time = 0.f;
				}
			}
			UIinfo::time += deltaTime * 4.f;
		}
	}
	ImGui::End();

}
void GameUI::MakeChoice(GameState& state, CharacterType& type)
{
	bool open = (state == GameState::MenuChoice);
	if(open)
	{
		ImGui::GetIO().WantCaptureKeyboard = true;
		static bool use_work_area = true;
		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
		ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
		ImGui::SetNextWindowBgAlpha(1.f);
		ImVec2 buttonSize = ImVec2(200, 50);
		bool StartLevel = false;
		if (ImGui::Begin("Example: Fullscreen window", &open, flags))
		{
			
			ImGui::Text("Choose your Character");
			if(CreateButtonCharacter(CharacterType::Wizard, "Wizard", buttonSize, ImVec2(150.f,80.f)))
			{
				type = CharacterType::Wizard;
				StartLevel = true;
				open = false;
			}
			if (CreateButtonCharacter(CharacterType::Warior, "Warrior", buttonSize, ImVec2(700.f, 80.f)))
			{
				type = CharacterType::Warior;
				StartLevel = true;
				open = false;
			}
			//ImGui::SameLine();
			if (CreateButtonCharacter(CharacterType::Hunter, "Hunter", buttonSize, ImVec2(150.f, 200.f)))
			{
				type = CharacterType::Hunter;
				StartLevel = true;
				open = false;
			}
			//ImGui::SameLine();
			if (CreateButtonCharacter(CharacterType::Elf, "Elf", buttonSize, ImVec2(700.f, 200.f)))
			{
				type = CharacterType::Elf;
				StartLevel = true;
				open = false;

			}
			ImGui::Separator();
			if (CreateButtonMiddle("Back", buttonSize, 2, viewport))
			{
				state = GameState::Menu;
				open = false;
			}
	
			if (StartLevel == true)
				state = GameState::Level;
		}
	}
		ImGui::End();
	

}
bool Filled = true;
void GameUI::SaveMenu(GameState& state, Scene& scene, CharacterType& type)
{
	bool open = (state == GameState::SaveMenu);
	if (open)
	{
		ImGui::GetIO().WantCaptureKeyboard = true;
		static bool use_work_area = true;
		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
		ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
		ImGui::SetNextWindowBgAlpha(1.f);
		ImVec2 buttonSize = ImVec2(200, 50);
		ImVec2 SizeSaveButton = ImVec2(400, 50);
	
		if (ImGui::Begin("SAVE menu", &open, flags))
		{
			ImGui::SetCursorPos(ImVec2((viewport->Size.x * 0.25f),
				10));
			ImGui::Text("Save Profiles");
			std::string saveslot[3] =
			{
				UIinfo::SaveSlot1,
				UIinfo::SaveSlot2,
				UIinfo::SaveSlot3
			};
			for(int i = 0; i < 3; i++)
			{
				if (UIinfo::SaveSlot1Used[i] != true)
				{
					std::string slot;
					ImGui::SetCursorPos(ImVec2((viewport->Size.x * 0.15f),
						(viewport->Size.y * 0.25f)));

					ImGui::PushID("slot1");
					if (i == 0)
					{
						ImGui::InputTextWithHint(" ", "Name player", UIinfo::SaveSlot1, 128);
						slot = UIinfo::SaveSlot1;
					}
					else if (i == 1)
					{
						ImGui::InputTextWithHint(" ", "Name player", UIinfo::SaveSlot2, 128);
						slot = UIinfo::SaveSlot2;

					}
					else
					{
						ImGui::InputTextWithHint(" ", "Name player", UIinfo::SaveSlot3, 128);
						slot = UIinfo::SaveSlot3;

					}
					ImGui::PopID();


					ImGui::PushID("new");
				
					ImGui::SameLine();
					if (ImGui::Button("New game"))
					{
						if (slot.empty())
						{
							Filled = false;
						}
						else
						{
							UIinfo::SaveSlot1Used[i] = true;
							std::string output = "Resources/PlayerData/" + slot + ".Scene";
							scene.Serialize(output, slot);
							UIinfo::currentGameSlot = slot;
							state = GameState::MenuChoice;
							Filled = true;

						}
						//open = false;
					}
					if(!Filled)
						ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Must fill in name");

					ImGui::PopID();

				}
				else
				{
					std::string slotOut;
					if (i == 0)
					{
						if (CreateButtonMiddle(UIinfo::SaveSlot1, SizeSaveButton, 5, viewport))
						{
							slotOut = UIinfo::SaveSlot1;
							scene.Deserialize("Resources/PlayerData/" + slotOut + ".Scene");
							UIinfo::currentGameSlot = slotOut;

							state = GameState::Level;

							//Load saved gamedata
						}
					}
					else if (i == 1)
					{

						if (CreateButtonMiddle(UIinfo::SaveSlot2, SizeSaveButton, 6, viewport))
						{
							slotOut = UIinfo::SaveSlot2;
							scene.Deserialize(slotOut + ".Scene");
							UIinfo::currentGameSlot = slotOut;

							state = GameState::Level;

							//Load saved gamedata
						}
					}
					else 
					{
						if(CreateButtonMiddle(UIinfo::SaveSlot3, SizeSaveButton, 7, viewport))
						{
							slotOut = UIinfo::SaveSlot3;
							scene.Deserialize(slotOut + ".Scene");
							UIinfo::currentGameSlot = slotOut;

							state = GameState::Level;

							//Load saved gamedata
						}	
					}
					
				}
	
			}
			ImGui::Separator();
			if(CreateButtonMiddle("Debug", buttonSize, 3, viewport))
			{
				state = GameState::Debug;
				type = CharacterType::Debug;
				open = false;

			}
			if (CreateButtonMiddle("Back", buttonSize, 4, viewport))
			{
				state = GameState::Menu;
				open = false;
			}
		}
	}
	ImGui::End();


}

void GameUI::GameStart( GameState& state)
{
	bool open = (state == GameState::Menu);
	if(open)
	{
		//choice = false;
		ImGui::GetIO().WantCaptureKeyboard = true;
		static bool use_work_area = true;
		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
		ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
		ImGui::SetNextWindowBgAlpha(1.f);
		ImVec2 buttonSize = ImVec2(200, 50);
		if (ImGui::Begin("beginscreen", &open, flags))
		{
			if (CreateButtonMiddle("Start", buttonSize, 6, viewport))
			{

				state = GameState::SaveMenu;
				//choice = true;
				open = false;
			}
			if (CreateButtonMiddle("Exit App", buttonSize, 5, viewport))
			{
				Application::Get()->WindowOpen = true;
				
			}
		}
	}
	ImGui::End();
};
void GameUI::GameEnd() 
{


};
