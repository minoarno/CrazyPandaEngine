#pragma once
#include "MiniginPCH.h"
#include "PrefabFactoryClass.h"
#include "Scene.h"

#include "TextureComponent.h"
#include "RigidBody.h"
#include "BoxCollider.h"

#include "EnemyComponent.h"
#include "FygarComponent.h"
#include "DigDugComponent.h"
#include "RockComponent.h"
#include "FireComponent.h"
#include "PumpComponent.h"
#include "Button.h"
#include "Lives.h"

using namespace dae;

dae::GameObject* CreatePlayer(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	gameobject->AddComponent(new Lives(3));
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 16,16 };
	auto pTexture = gameobject->AddComponent(new dae::TextureComponent{ "DigDug.png" });
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });

	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	DigDugComponent* pDigDug = gameobject->AddComponent(new DigDugComponent{});
	pDigDug->SetRespawn(pos);

	gameobject->SetPosition(pos);
	gameobject->SetTag("Player");
	return gameobject;
}

dae::GameObject* CreatePooka(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 16,16 };
	auto pTexture = gameobject->AddComponent(new dae::TextureComponent{ "Pooka.png" });
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });

	gameobject->AddComponent(new BoxCollider({dims.x, dims.y}, {dims.x / 2, dims.y / 2}));
	gameobject->AddComponent(new EnemyComponent{});

	gameobject->SetPosition(pos);
	gameobject->SetTag("Pooka");
	return gameobject;
}

dae::GameObject* CreateFygar(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 16,16 };
	auto pTexture = gameobject->AddComponent(new dae::TextureComponent{ "Fygar.png" });
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });

	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	gameobject->AddComponent(new FygarComponent{});
	
	gameobject->SetPosition(pos);
	gameobject->SetTag("Fygar");
	return gameobject;
}

dae::GameObject* CreateRock(dae::Scene& scene, const glm::vec2& pos)
{
	auto gameobject = scene.Add(new dae::GameObject{});
	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	const glm::vec2& dims{ 20,20 };
	auto texture = gameobject->AddComponent(new TextureComponent{ "Rock.png" });
	texture->SetSourceRect(Rectf{ 0,0,16.f,16.f });
	texture->SetDestinationRectDimensions({ dims.x, dims.y });

	gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	gameobject->AddComponent(new RockComponent{});

	gameobject->SetPosition(pos + glm::vec2{ 2,4 });
	gameobject->SetTag("Rock");
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

dae::GameObject* CreatePump(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims, int direction)
{
	auto gameobject = scene.Add(new dae::GameObject{});

	auto texture = gameobject->AddComponent(new TextureComponent{ "Pump.png" });
	texture->SetSourceRect(Rectf{ 0,direction * 32.f,32.f,32.f });
	texture->SetDestinationRectDimensions({ dims.x, dims.y });

	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	auto pBox = gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	pBox->SetIsTrigger(true);
	gameobject->AddComponent(new PumpComponent{ DigDugComponent::CharacterDirection(direction) });

	gameobject->SetPosition(pos);
	gameobject->SetTag("Pump");
	return gameobject;
}

dae::GameObject* CreateFire(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims)
{
	auto gameobject = scene.Add(new dae::GameObject{});

	auto texture = gameobject->AddComponent(new TextureComponent{ "Fire.png" });
	texture->SetSourceRect(Rectf{ 0,0,16.f,16.f });
	texture->SetDestinationRectDimensions({ dims.x, dims.y });

	auto pRigid = gameobject->AddComponent(new RigidBody());
	pRigid->SetGravityScale(0);

	auto pBox = gameobject->AddComponent(new BoxCollider({ dims.x, dims.y }, { dims.x / 2, dims.y / 2 }));
	pBox->SetIsTrigger(true);
	gameobject->AddComponent(new FireComponent{});

	gameobject->SetPosition(pos);
	gameobject->SetTag("Fire");
	return gameobject;
}

dae::GameObject* CreateButton(dae::Scene& scene, const glm::vec2& pos, const glm::vec2& dims, const std::string& texture, Command* pCommand)
{
	auto gameobject = scene.Add(new dae::GameObject{});

	auto pTexture = gameobject->AddComponent(new TextureComponent{ texture });
	pTexture->SetDestinationRectDimensions({ dims.x, dims.y });
	
	gameobject->AddComponent(new Button{ dims,pCommand });
	
	gameobject->SetPosition(pos);
	return gameobject;
}
