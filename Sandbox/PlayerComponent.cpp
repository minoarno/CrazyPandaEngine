#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "Lives.h"
#include "ScoreManager.h"

PlayerComponent::PlayerComponent(int amountOfLives)
	: BaseComponent{}
	, m_pLives{ std::make_shared<Lives>( amountOfLives )}
{
}

void PlayerComponent::Dies()
{
	m_pLives->LoseLife();
}

void PlayerComponent::AddScore(int score)
{
	ScoreManager::GetInstance().IncreaseScore(score);
}
