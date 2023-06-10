#include "MiniginPCH.h"
#include "DigDugComponent.h"
#include "Scene.h"
#include "PrefabFactoryClass.h"

DigDugComponent::DigDugComponent()
{
}

void DigDugComponent::PumpAttack()
{
	auto pos = m_pGameObject->GetTransform()->GetWorldPosition();
	CreatePump(*m_pGameObject->GetScene(),{}, {});
}

void DigDugComponent::SetDirection(CharacterDirection direction)
{
}

void DigDugComponent::SetState(CharacterState state)
{
	if (true)
	{

	}
}

void DigDugComponent::Initialize()
{
}

void DigDugComponent::Update()
{
}
