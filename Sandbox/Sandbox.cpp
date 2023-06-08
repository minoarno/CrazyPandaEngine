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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");

	auto pLevel = scene.Add(new dae::GameObject{});

	JsonHelper::LoadSceneUsingJson("Levels/Level1.json", pLevel);
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

	ServiceLocator::GetAudio().AddSound("bell.wav");
	ServiceLocator::GetAudio().PlaySound(0);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}