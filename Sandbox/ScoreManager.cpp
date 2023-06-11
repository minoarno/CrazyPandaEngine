#include "MiniginPCH.h"
#include "ScoreManager.h"

void ScoreManager::ResetScore()
{
    m_Score = 0;
}

void ScoreManager::IncreaseScore(int amount)
{
    m_Score += amount;
    Notify(this);
}

int ScoreManager::GetScore() const
{
    return m_Score;
}

void ScoreManager::SetHeightLevels(const std::vector<float>& heights)
{
    m_Heights = heights;
    std::sort(m_Heights.begin(), m_Heights.end());
}

int ScoreManager::GetHeightMultiplier(float yLevel)
{
    for (int i = 0; i < int(m_Heights.size()); i++)
    {
        if (yLevel < m_Heights[i])
        {
            return i + 2;
        }
    }
    return 5;
}
