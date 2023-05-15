#include "MiniginPCH.h"
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Command.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"

#include "InputManager.h"
#include "Lives.h"
#include "LivesDisplay.h"
#include "ScoreDisplay.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto gameobject = std::make_shared<dae::GameObject>();
	gameobject->AddComponent(new dae::TextureComponent("background.tga"));
	scene.Add(gameobject);

	gameobject = std::make_shared<dae::GameObject>();
	gameobject->AddComponent(new dae::TextureComponent("logo.tga"));
	gameobject->SetPosition(216, 180);
	scene.Add(gameobject);

	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	gameobject = std::make_shared<dae::GameObject>();
	gameobject->AddComponent(new dae::TextComponent(font, "Programming 4 Assignment"));
	gameobject->SetPosition(80, 20);
	scene.Add(gameobject);

	gameobject = std::make_shared<dae::GameObject>();
	dae::TextComponent* pTextComponent = gameobject->AddComponent(new dae::TextComponent(font, "0 FPS"));
	pTextComponent->SetColor(Colorf{ 255,0,0 });
	gameobject->AddComponent(new dae::FpsComponent());
	gameobject->SetPosition(20, 50);
	scene.Add(gameobject);

	gameobject = std::make_shared<dae::GameObject>();
	gameobject->SetPosition(216, 180);

	auto* texture = gameobject->AddComponent(new dae::TextureComponent("SpritesDigDug.png"));
	texture->SetSourceRect(Rectf{ 0,0,40,40 });
	texture->SetDestinationRectDimensions(glm::vec2{ 20.f,20.f });
	scene.Add(gameobject);

	//float speed{ 180.f };

	//InputManager::GetInstance().AddOnHold(SDLK_q, new MoveCommand{gameobject.get(),glm::fvec3{-speed,0,0}});
	//InputManager::GetInstance().AddOnHold(SDLK_d, new MoveCommand{gameobject.get(),glm::fvec3{speed,0,0}});
	//InputManager::GetInstance().AddOnHold(SDLK_s, new MoveCommand{gameobject.get(),glm::fvec3{0,speed,0}});
	//InputManager::GetInstance().AddOnHold(SDLK_z, new MoveCommand{gameobject.get(),glm::fvec3{0,-speed,0}});

	PlayerComponent* pPlayerComponent = gameobject->AddComponent(new PlayerComponent{ 5 });

	InputManager::GetInstance().AddOnPressDown(SDLK_e, new DieCommand{ pPlayerComponent });
	InputManager::GetInstance().AddOnPressDown(SDLK_r, new ScoreIncrementCommand{ pPlayerComponent });

	gameobject = std::make_shared<dae::GameObject>();
	gameobject->AddComponent(new LivesDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 100);
	scene.Add(gameobject);
	gameobject = std::make_shared<dae::GameObject>();
	gameobject->AddComponent(new ScoreDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 140);
	scene.Add(gameobject);

	gameobject = std::make_shared<dae::GameObject>();
	gameobject->SetPosition(200, 80);
	texture = gameobject->AddComponent(new dae::TextureComponent("SpritesDigDug.png"));
	scene.Add(gameobject);

	texture->SetSourceRect(Rectf{ 0,0,40,40 });
	texture->SetDestinationRectDimensions(glm::vec2{ 20.f,20.f });

	//InputManager::GetInstance().AddOnHold(SDLK_LEFT, new MoveCommand{ gameobject.get(),glm::fvec3{-speed,0,0} });
	//InputManager::GetInstance().AddOnHold(SDLK_RIGHT, new MoveCommand{ gameobject.get(),glm::fvec3{speed,0,0} });
	//InputManager::GetInstance().AddOnHold(SDLK_DOWN, new MoveCommand{ gameobject.get(),glm::fvec3{0,speed,0} });
	//InputManager::GetInstance().AddOnHold(SDLK_UP, new MoveCommand{ gameobject.get(),glm::fvec3{0,-speed,0} });

	pPlayerComponent = gameobject->AddComponent(new PlayerComponent{ 5 });

	InputManager::GetInstance().AddOnPressDown(SDLK_KP_MINUS, new DieCommand{ pPlayerComponent });
	InputManager::GetInstance().AddOnPressDown(SDLK_KP_PLUS, new ScoreIncrementCommand{ pPlayerComponent });

	gameobject = std::make_shared<dae::GameObject>();
	gameobject->AddComponent(new LivesDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 200);
	scene.Add(gameobject);
	gameobject = std::make_shared<dae::GameObject>();
	gameobject->AddComponent(new ScoreDisplay{ pPlayerComponent });
	gameobject->SetPosition(20, 240);
	scene.Add(gameobject);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}