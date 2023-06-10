#pragma once
#include "MiniginPCH.h"
#include "PrefabFactoryClass.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "RigidBody.h"
#include "BoxCollider.h"

#include "EnemyComponent.h"
#include "PookaComponent.h"
#include "FygarComponent.h"
#include "DigDugComponent.h"
#include "FireComponent.h"
#include "PumpComponent.h"

using namespace dae;

dae::GameObject* CreatePlayer(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 16,16 };

	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	gameobject->AddComponent(new DigDugComponent{});

	auto pTexture = gameobject->AddComponent(new dae::TextureComponent{ "DigDug.png" });
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });
	gameobject->SetPosition(pos);
	return gameobject;
}

dae::GameObject* CreatePooka(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 16,16 };

	gameobject->AddComponent(new BoxCollider({dims.x, dims.y}, {dims.x / 2, dims.y / 2}));
	gameobject->AddComponent(new PookaComponent{});

	auto pTexture = gameobject->AddComponent(new dae::TextureComponent{ "Pooka.png" });
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });
	gameobject->SetPosition(pos);
	return gameobject;
}

dae::GameObject* CreateFygar(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 16,16 };

	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	gameobject->AddComponent(new FygarComponent{});
	gameobject->SetPosition(pos);
	return gameobject;
}

dae::GameObject* CreateRock(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 16,16 };

	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	gameobject->AddComponent(new FygarComponent{});
	gameobject->SetPosition(pos);

	gameobject->SetPosition(pos);
	return gameobject;
}

dae::GameObject* CreateBlock(dae::GameObject* pLevel, const glm::vec2& pos, const glm::vec2& dims, int index)
{
	auto gameobject = pLevel->AddChild(new dae::GameObject{});
	gameobject->AddComponent(new RigidBody(true));
	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));

	auto texture = gameobject->AddComponent(new TextureComponent{ "Blocks.png" });
	texture->SetSourceRect(Rectf{ 0,index * 8.f,8.f,8.f });
	texture->SetDestinationRectDimensions({ dims.x, dims.y });

	gameobject->SetPosition(pos);

	return gameobject;
}

dae::GameObject* CreatePump(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	auto pBox = gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	pBox->SetIsTrigger(true);
	gameobject->AddComponent(new FireComponent{});
	gameobject->SetPosition(pos);

	gameobject->SetPosition(pos);
	return gameobject;
}

dae::GameObject* CreateFire(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	auto pBox = gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	pBox->SetIsTrigger(true);
	gameobject->AddComponent(new FireComponent{});
	gameobject->SetPosition(pos);

	gameobject->SetPosition(pos);
	return gameobject;
}
