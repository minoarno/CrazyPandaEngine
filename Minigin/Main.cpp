#include "MiniginPCH.h"
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "RotatorComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("background.tga"));
	scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextureComponent("logo.tga"));
	go->SetPosition(216, 180);
	scene.Add(go);
	
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent(new dae::TextComponent(font, "Programming 4 Assignment"));
	go->SetPosition(80, 20);
	scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	dae::TextComponent* pTextComponent = go->AddComponent(new dae::TextComponent(font, "0 FPS"));
	pTextComponent->SetColor(Colorf{ 255,0,0 });
	go->AddComponent(new dae::FpsComponent());
	go->SetPosition(20, 50);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->SetPosition(216, 180);
	scene.Add(go);

	auto kid = go->AddChild(new dae::GameObject());
	auto texture = kid->AddComponent(new dae::TextureComponent("SpritesDigDug.png"));
	texture->SetSourceRect(Rectf{0,0,40,40});
	texture->SetDestinationRectDimensions(Vector2f{20,20});
	kid->AddComponent(new dae::RotatorComponent(50,30));
	
	auto kid2 = kid->AddChild(new dae::GameObject());
	texture = kid2->AddComponent(new dae::TextureComponent("SpritesDigDug.png"));
	texture->SetSourceRect(Rectf{0,0,40,40});
	texture->SetDestinationRectDimensions(Vector2f{20,20});
	kid2->AddComponent(new dae::RotatorComponent(-80,30));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);


    return 0;
}