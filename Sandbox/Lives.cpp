#include "MiniginPCH.h"
#include "Lives.h"
#include "GameStateManager.h"

Lives::Lives(int amount)
	: m_AmountOfLives{ amount }
{
}

void Lives::LoseLife()
{
	if (m_AmountOfLives == 0)
	{
		GameStateManager::GetInstance().GoToEndScene();
	}

	m_AmountOfLives--;
	Notify(this);
}

void Lives::GainLife()
{
	m_AmountOfLives++;
	Notify(this);
}
