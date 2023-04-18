#include "MiniginPCH.h"
#include "Lives.h"

Lives::Lives(int amount)
	: m_AmountOfLives{ amount }
{
}

void Lives::LoseLife()
{
	m_AmountOfLives--;
	Notify(this);
}

void Lives::GainLife()
{
	m_AmountOfLives++;
	Notify(this);
}
