#include "MiniginPCH.h"
#include "Score.h"

void Score::IncreaseScore(int amount)
{
    m_Score += amount;
    Notify(this);
}

int Score::GetScore() const
{
    return m_Score;
}
