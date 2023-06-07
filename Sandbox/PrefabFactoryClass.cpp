#pragma once
#include "MiniginPCH.h"
#include "PrefabFactoryClass.h"
#include "GameObject.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "RigidBody.h"
#include "BoxCollider.h"

using namespace dae;

dae::GameObject* CreatePlayer(dae::Scene& scene)
{
	auto gameobject = scene.Add(std::make_shared<dae::GameObject>());
	return gameobject.get();
}

dae::GameObject* CreatePooka(dae::Scene& scene)
{
	auto gameobject = scene.Add(std::make_shared<dae::GameObject>());
	return gameobject.get();
}

dae::GameObject* CreateFygar(dae::Scene& scene)
{
	auto gameobject = scene.Add(std::make_shared<dae::GameObject>());
	return gameobject.get();
}

dae::GameObject* CreateRock(dae::Scene& scene)
{
	auto gameobject = scene.Add(std::make_shared<dae::GameObject>());
	return gameobject.get();
}

dae::GameObject* CreateBlock(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims)
{
	auto gameobject = scene.Add(std::make_shared<dae::GameObject>());
	gameobject->SetPosition(pos);
	//gameobject->SetScene(pScene);

	auto texture = gameobject->AddComponent(new TextureComponent{ "LevelBlock.png" });
	texture->SetDestinationRectDimensions({ dims.x, dims.y });

	gameobject->AddComponent(new RigidBody(true));
	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	return gameobject.get();
}
