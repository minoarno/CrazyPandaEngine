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
	switch (m_Direction)
	{
	case CharacterDirection::Down:
		pos.y += 16;
		break;
	case CharacterDirection::Up:
		pos.y -= 32;
		break;
	case CharacterDirection::Left:
		pos.x -= 32;
		break;
	case CharacterDirection::Right:
	default:
		pos.x += 16;
		break;
	}

	CreatePump(*m_pGameObject->GetScene(),{pos.x,pos.y}, {32,32}, int(m_Direction));
}

void DigDugComponent::SetDirection(CharacterDirection direction)
{
	m_Direction = direction;
}

void DigDugComponent::SetState(CharacterState state)
{
	if (m_State == state)return;


}

void DigDugComponent::Initialize()
{
}

void DigDugComponent::Update()
{
}
