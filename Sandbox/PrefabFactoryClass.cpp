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
	auto gameobject = scene.Add(new dae::GameObject{});
	return gameobject;
}

dae::GameObject* CreatePooka(dae::Scene& scene)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	return gameobject;
}

dae::GameObject* CreateFygar(dae::Scene& scene)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	return gameobject;
}

dae::GameObject* CreateRock(dae::Scene& scene)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	return gameobject;
}

dae::GameObject* CreateBlock(dae::GameObject* pLevel, const glm::vec2& pos, const glm::vec2& dims, int index)
{
	auto gameobject = pLevel->AddChild(new dae::GameObject{});
	gameobject->SetPosition(pos);

	auto texture = gameobject->AddComponent(new TextureComponent{ "Blocks.png" });
	texture->SetSourceRect(Rectf{ 0,index * 8.f,8.f,8.f });
	texture->SetDestinationRectDimensions({ dims.x, dims.y });

	gameobject->AddComponent(new RigidBody(true));
	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	return gameobject;
}
