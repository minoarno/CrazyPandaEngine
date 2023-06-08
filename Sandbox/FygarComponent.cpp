#include "MiniginPCH.h"
#include "FygarComponent.h"

#include "TextureComponent.h"

FygarComponent::FygarComponent()
	: EnemyComponent{}
{
}

void FygarComponent::Initialize()
{
	EnemyComponent::Initialize();
	auto pTexture = m_pGameObject->AddComponent(new dae::TextureComponent{ "Fygar.png" });
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });
}
