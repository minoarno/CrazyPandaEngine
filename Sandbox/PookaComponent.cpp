#include "MiniginPCH.h"
#include "PookaComponent.h"

#include "TextureComponent.h"

PookaComponent::PookaComponent()
	: EnemyComponent{}
{
}

void PookaComponent::Initialize()
{
	//EnemyComponent::Initialize();
	auto pTexture = m_pGameObject->AddComponent(new dae::TextureComponent{"Pooka.png"});
	pTexture->SetDestinationRectDimensions({ 16, 16 });
	pTexture->SetSourceRect({ 0,0,16,16 });
}
