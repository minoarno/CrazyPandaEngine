#include "MiniginPCH.h"
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "SandboxCommands.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "PlayerControllerFygar.h"

#include "InputManager.h"
#include "Lives.h"
#include "LivesDisplay.h"
#include "ScoreDisplay.h"

#include "ServiceLocator.h"

#include "JsonHelper.h"
#include "PrefabFactoryClass.h"

#include <deque>
#include <string>
#include "ScoreManager.h"
#include "GameStateManager.h"

enum class Mode
{
	Singleplayer,
	Coop,
	Versus
};

void MainMenu()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MainMenu");

	CreateButton(scene, { 200,100 }, { 200,60 }, "UISingle.png", new StartGameCommand("Level1", { "Level2", "Level3" }));
	CreateButton(scene, {200,200}, { 200,60 }, "UICoop.png", new StartGameCommand{ "Level1C", {"Level2C","Level3C"} });
	CreateButton(scene, { 200,300 }, { 200,60 }, "UIVersus.png", new StartGameCommand{ "Level1V", { "Level2V","Level3V"} });

	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), SDLK_F1, new LoadSceneCommand{ "Level1" });
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), SDLK_F2, new MuteCommand{ });
}

void AddLevel(const std::string& scenename, const std::string& levelFilename, const std::string& nextSceneName, Mode mode)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(scenename);

	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson(levelFilename, pLevel);

	auto gameobject = CreatePlayer(scene, { 300,70 });
	float speed{ 1000.f };
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), SDLK_F1, new LoadSceneCommand{ nextSceneName });
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), SDLK_F2, new MuteCommand{ });

	int playerIndex = 0;
	InputManager::GetInstance().AddOnHold(scene.GetIndex(), SDLK_q, new DigDugMoveCommand{gameobject,glm::fvec3{-speed,0,0}, DigDugComponent::CharacterDirection::Left});
	InputManager::GetInstance().AddOnHold(scene.GetIndex(), SDLK_d, new DigDugMoveCommand{ gameobject,glm::fvec3{speed,0,0}, DigDugComponent::CharacterDirection::Right });
	InputManager::GetInstance().AddOnHold(scene.GetIndex(), SDLK_s, new DigDugMoveCommand{ gameobject,glm::fvec3{0,speed,0}, DigDugComponent::CharacterDirection::Down });
	InputManager::GetInstance().AddOnHold(scene.GetIndex(), SDLK_z, new DigDugMoveCommand{ gameobject,glm::fvec3{0,-speed,0}, DigDugComponent::CharacterDirection::Up });
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::DPadLeft, new DigDugMoveCommand{ gameobject,glm::fvec3{-speed,0,0}, DigDugComponent::CharacterDirection::Left }, playerIndex);
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::DPadRight, new DigDugMoveCommand{ gameobject,glm::fvec3{speed,0,0}, DigDugComponent::CharacterDirection::Right }, playerIndex);
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::DPadDown, new DigDugMoveCommand{ gameobject,glm::fvec3{0,speed,0}, DigDugComponent::CharacterDirection::Down }, playerIndex);
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(),ControllerButton::DPadUp, new DigDugMoveCommand{ gameobject,glm::fvec3{0,-speed,0}, DigDugComponent::CharacterDirection::Up }, playerIndex);

	DigDugComponent* pDigDug = gameobject->GetComponent<DigDugComponent>();
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(),SDLK_e, new DigDugPumpCommand{ pDigDug });
	InputManager::GetInstance().AddOnPressDown(scene.GetIndex(),ControllerButton::ButtonA, new DigDugPumpCommand{ pDigDug }, playerIndex);

	auto pLives = scene.Add(new dae::GameObject{});
	pLives->AddComponent(new LivesDisplay{ gameobject->GetComponent<Lives>() });
	pLives->SetPosition({ 200,450 });

	dae::GameObject* pScore;
	PlayerControllerFygar* pFygar;
	switch (mode)
	{
	case Mode::Singleplayer:
		pScore = scene.Add(new dae::GameObject{});
		pScore->AddComponent(new ScoreDisplay{});
		pScore->SetPosition({ 10,450 });
		break;
	case Mode::Coop:
		gameobject = CreatePlayer(scene, { 300,200 });

		playerIndex = 1;
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(),ControllerButton::DPadLeft, new DigDugMoveCommand{ gameobject,glm::fvec3{-speed,0,0}, DigDugComponent::CharacterDirection::Left }, playerIndex);
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(),ControllerButton::DPadRight, new DigDugMoveCommand{ gameobject,glm::fvec3{speed,0,0}, DigDugComponent::CharacterDirection::Right }, playerIndex);
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(),ControllerButton::DPadDown, new DigDugMoveCommand{ gameobject,glm::fvec3{0,speed,0}, DigDugComponent::CharacterDirection::Down }, playerIndex);
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(),ControllerButton::DPadUp, new DigDugMoveCommand{ gameobject,glm::fvec3{0,-speed,0}, DigDugComponent::CharacterDirection::Up }, playerIndex);

		pDigDug = gameobject->GetComponent<DigDugComponent>();
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::ButtonA, new DigDugPumpCommand{ pDigDug }, playerIndex);

		pLives = scene.Add(new dae::GameObject{});
		pLives->AddComponent(new LivesDisplay{ gameobject->GetComponent<Lives>() });
		pLives->SetPosition({ 400,450 });

		pScore = scene.Add(new dae::GameObject{});
		pScore->AddComponent(new ScoreDisplay{});
		pScore->SetPosition({ 10,450 });
		break;
	case Mode::Versus:
		gameobject = CreatePlayerFygar(scene, { 300,200 });

		playerIndex = 1;
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::DPadLeft, new FygarMoveCommand{ gameobject,glm::fvec3{-speed,0,0} }, playerIndex);
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::DPadRight, new FygarMoveCommand{ gameobject,glm::fvec3{speed,0,0} }, playerIndex);
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::DPadDown, new FygarMoveCommand{ gameobject,glm::fvec3{0,speed,0} }, playerIndex);
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::DPadUp, new FygarMoveCommand{ gameobject,glm::fvec3{0,-speed,0} }, playerIndex);

		pFygar = gameobject->GetComponent<PlayerControllerFygar>();
		InputManager::GetInstance().AddOnPressDown(scene.GetIndex(), ControllerButton::ButtonA, new FygarFireCommand{ pFygar }, playerIndex);

		pLives = scene.Add(new dae::GameObject{});
		pLives->AddComponent(new LivesDisplay{ gameobject->GetComponent<Lives>() });
		pLives->SetPosition({ 400,450 });

		pScore = scene.Add(new dae::GameObject{});
		pScore->AddComponent(new ScoreDisplay{});
		pScore->SetPosition({ 10,450 });
		break;
	default:
		break;
	}

	scene.SetOnAttach([&]()
		{
			GameStateManager::GetInstance().ResetEnemies();
		});
}

void HighScore()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("HighScore");
	CreateButton(scene, { 200,400 }, { 200,60 }, "MainMenu.png", new LoadSceneCommand{ "MainMenu" });

	CreateHighScore(scene, { 200,40 }, "Levels/HighScore.json");

	InputManager::GetInstance().AddOnHold(scene.GetIndex(),SDLK_F1, new LoadSceneCommand{ "MainMenu" });
}

void LoadScenes()
{
	ScoreManager::GetInstance().ResetScore();

	MainMenu();
	AddLevel("Level1", "Levels/Level1.json", "Level2", Mode::Singleplayer);
	AddLevel("Level2", "Levels/Level2.json", "Level3", Mode::Singleplayer);
	AddLevel("Level3", "Levels/Level3.json", "MainMenu", Mode::Singleplayer);

	AddLevel("Level1C", "Levels/Level1.json", "Level2C", Mode::Coop);
	AddLevel("Level2C", "Levels/Level2.json", "Level3C", Mode::Coop);
	AddLevel("Level3C", "Levels/Level3.json", "MainMenu", Mode::Coop);

	AddLevel("Level1V", "Levels/Level1.json", "MainMenu", Mode::Versus);
	HighScore();

	ServiceLocator::GetAudio().AddSound("Sound/Stage Theme.wav");
	ServiceLocator::GetAudio().AddSound("Sound/Stage Clear.wav");
	ServiceLocator::GetAudio().AddSound("Sound/Fygar Flame.wav");

	ServiceLocator::GetAudio().PlaySound(0);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(LoadScenes);

	return 0;
}