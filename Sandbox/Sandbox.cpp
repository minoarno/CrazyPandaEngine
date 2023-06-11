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

#include "InputManager.h"
#include "Lives.h"
#include "LivesDisplay.h"
#include "ScoreDisplay.h"

#include "ServiceLocator.h"

#include "RigidBody.h"
#include "BoxCollider.h"

#include "JsonHelper.h"
#include "PrefabFactoryClass.h"

void MainMenu()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	CreateButton(scene, {200,100}, { 200,60 }, "UISingle.png", new LoadSceneCommand{ "Level1" });
	CreateButton(scene, {200,200}, { 200,60 }, "UICoop.png", new LoadSceneCommand{ "MultiplayerLevel1" });
	CreateButton(scene, {200,300}, { 200,60 }, "UIVersus.png", new LoadSceneCommand{ "VersusLevel1" });
}

void Level1()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");

	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level1.json", pLevel);

	auto gameobject = CreatePlayer(scene, { 300,70 });
	float speed{ 1000.f };
	InputManager::GetInstance().AddOnHold(SDLK_F1, new LoadSceneCommand{ "Level2" });
	
	InputManager::GetInstance().AddOnHold(SDLK_q, new DigDugMoveCommand{ gameobject,glm::fvec3{-speed,0,0}, DigDugComponent::CharacterDirection::Left });
	InputManager::GetInstance().AddOnHold(SDLK_d, new DigDugMoveCommand{ gameobject,glm::fvec3{speed,0,0}, DigDugComponent::CharacterDirection::Right });
	InputManager::GetInstance().AddOnHold(SDLK_s, new DigDugMoveCommand{ gameobject,glm::fvec3{0,speed,0}, DigDugComponent::CharacterDirection::Down });
	InputManager::GetInstance().AddOnHold(SDLK_z, new DigDugMoveCommand{ gameobject,glm::fvec3{0,-speed,0}, DigDugComponent::CharacterDirection::Up });
	InputManager::GetInstance().AddOnHold(ControllerButton::DPadLeft, new DigDugMoveCommand{ gameobject,glm::fvec3{-speed,0,0}, DigDugComponent::CharacterDirection::Left }, 0);
	InputManager::GetInstance().AddOnHold(ControllerButton::DPadRight, new DigDugMoveCommand{ gameobject,glm::fvec3{speed,0,0}, DigDugComponent::CharacterDirection::Right }, 0);
	InputManager::GetInstance().AddOnHold(ControllerButton::DPadDown, new DigDugMoveCommand{ gameobject,glm::fvec3{0,speed,0}, DigDugComponent::CharacterDirection::Down }, 0);
	InputManager::GetInstance().AddOnHold(ControllerButton::DPadUp, new DigDugMoveCommand{ gameobject,glm::fvec3{0,-speed,0}, DigDugComponent::CharacterDirection::Up }, 0);

	DigDugComponent* pDigDug = gameobject->GetComponent<DigDugComponent>();
	InputManager::GetInstance().AddOnPressDown(SDLK_e, new DigDugPumpCommand{ pDigDug });
	InputManager::GetInstance().AddOnPressDown(ControllerButton::ButtonA, new DigDugPumpCommand{ pDigDug }, 0);
}

void Level2()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level2.json", pLevel);
}

void Level3()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level3.json", pLevel);
}

void Level1Multiplayer()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MultiplayerLevel1");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level1.json", pLevel);
}


void Level2Multiplayer()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MultiplayerLevel2");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level2.json", pLevel);
}


void Level3Multiplayer()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MultiplayerLevel3");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level3.json", pLevel);
}

void Level1Versus()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("VersusLevel1");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level1.json", pLevel);
}


void Level2Versus()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("VersusLevel2");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level2.json", pLevel);
}


void Level3Versus()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("VersusLevel3");
	auto pLevel = scene.Add(new dae::GameObject{});
	JsonHelper::LoadSceneUsingJson("Levels/Level3.json", pLevel);
}

void HighScore()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("HighScore");
	CreateButton(scene, { 200,100 }, { 200,60 }, "UISingle.png", new LoadSceneCommand{ "MainMenu" });

	InputManager::GetInstance().AddOnHold(SDLK_F1, new LoadSceneCommand{ "MainMenu" });
}

void LoadScenes()
{
	MainMenu();
	Level1();
	Level2();
	Level3();
	Level1Multiplayer();
	Level2Multiplayer();
	Level3Multiplayer();
	Level1Versus();
	Level2Versus();
	Level3Versus();
}

void Demo()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new dae::TextureComponent("background.tga"));


	gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new dae::TextureComponent("logo.tga"));
	gameobject->SetPosition(216, 180);

	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new dae::TextComponent(font, "Programming 4 Assignment"));
	gameobject->SetPosition(80, 20);

	gameobject = scene.Add(new dae::GameObject{});
	dae::TextComponent* pTextComponent = gameobject->AddComponent(new dae::TextComponent(font, "0 FPS"));
	pTextComponent->SetColor(Colorf{ 255,0,0 });
	gameobject->AddComponent(new dae::FpsComponent());
	gameobject->SetPosition(20, 50);

	gameobject = scene.Add(new dae::GameObject{});
	gameobject->SetPosition(216, 180);

	auto* texture = gameobject->AddComponent(new dae::TextureComponent("SpritesDigDug.png"));
	gameobject->AddComponent(new RigidBody{ false });
	gameobject->AddComponent(new BoxCollider{ {20.f,20.f} });
	texture->SetSourceRect(Rectf{ 0,0,40,40 });
	texture->SetDestinationRectDimensions(glm::vec2{ 20.f,20.f });

	float speed{ 180.f };

	InputManager::GetInstance().AddOnHold(SDLK_q, new MoveCommand{ gameobject,glm::fvec3{-speed,0,0} });
	InputManager::GetInstance().AddOnHold(SDLK_d, new MoveCommand{ gameobject,glm::fvec3{speed,0,0} });
	InputManager::GetInstance().AddOnHold(SDLK_s, new MoveCommand{ gameobject,glm::fvec3{0,speed,0} });
	InputManager::GetInstance().AddOnHold(SDLK_z, new MoveCommand{ gameobject,glm::fvec3{0,-speed,0} });

	PlayerComponent* pPlayerComponent = gameobject->AddComponent(new PlayerComponent{ 5 });

	InputManager::GetInstance().AddOnPressDown(SDLK_e, new DieCommand{ pPlayerComponent });
	InputManager::GetInstance().AddOnPressDown(SDLK_r, new ScoreIncrementCommand{ pPlayerComponent });

	gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new LivesDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 100);

	gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new ScoreDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 140);


	gameobject = scene.Add(new dae::GameObject{});
	gameobject->SetPosition(200, 80);
	texture = gameobject->AddComponent(new dae::TextureComponent("SpritesDigDug.png"));
	texture->SetSourceRect(Rectf{ 0,0,40,40 });
	texture->SetDestinationRectDimensions(glm::vec2{ 20.f,20.f });
	gameobject->AddComponent(new RigidBody{ false });
	gameobject->AddComponent(new BoxCollider{ {20.f,20.f} });

	InputManager::GetInstance().AddOnHold(SDLK_LEFT, new MoveCommand{ gameobject,glm::fvec3{-speed,0,0} });
	InputManager::GetInstance().AddOnHold(SDLK_RIGHT, new MoveCommand{ gameobject,glm::fvec3{speed,0,0} });
	InputManager::GetInstance().AddOnHold(SDLK_DOWN, new MoveCommand{ gameobject,glm::fvec3{0,speed,0} });
	InputManager::GetInstance().AddOnHold(SDLK_UP, new MoveCommand{ gameobject,glm::fvec3{0,-speed,0} });

	pPlayerComponent = gameobject->AddComponent(new PlayerComponent{ 5 });

	InputManager::GetInstance().AddOnPressDown(SDLK_KP_MINUS, new DieCommand{ pPlayerComponent });
	InputManager::GetInstance().AddOnPressDown(SDLK_KP_PLUS, new ScoreIncrementCommand{ pPlayerComponent });

	gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new LivesDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 200);

	gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new ScoreDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 240);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(LoadScenes);

	return 0;
}