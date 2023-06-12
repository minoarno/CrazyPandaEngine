#include "MiniginPCH.h"
#include "PlayerControllerFygar.h"
#include "GameStateManager.h"
#include "EngineTime.h"

void PlayerControllerFygar::StartFire()
{
	Fire();
}

void PlayerControllerFygar::Update()
{
	if (m_HasToBeAddedToList)
	{
		GameStateManager::GetInstance().OnEnemySpawn();
		m_HasToBeAddedToList = false;
	}

	switch (m_State)
	{
	case EnemyState::Walk:
	default:
		break;
	case EnemyState::Crushed:
		Crushed();
		break;
	case EnemyState::Bloated:
		Bloated();
		break;
	case EnemyState::Ghost:
		Ghost();
		break;
	case EnemyState::Fire:
		Fire();
		break;
	}

	if (m_LastAnimationTime + m_AnimationDuration > Time::GetInstance().GetTotalSeconds()) return;

	m_CurrentAnimationIndex++;
	UpdateTexture();
}
