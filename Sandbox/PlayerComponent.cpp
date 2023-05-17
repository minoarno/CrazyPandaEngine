#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "Lives.h"
#include "Score.h"

PlayerComponent::PlayerComponent(int amountOfLives)
	: BaseComponent{}
	, m_pLives{ new Lives{amountOfLives} }
	, m_pScore{ new Score{} }
{
}

PlayerComponent::~PlayerComponent()
{
	delete m_pLives;
	m_pLives = nullptr;

	delete m_pScore;
	m_pScore = nullptr;
}

void PlayerComponent::Dies()
{
	m_pLives->LoseLife();
}

void PlayerComponent::AddScore(int score)
{
	m_pScore->IncreaseScore(score);
}
