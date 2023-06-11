#include "MiniginPCH.h"
#include "HighScoreComponent.h"

#include "JsonHelper.h"

HighScoreComponent::HighScoreComponent(const std::string& filepath)
{
	JsonHelper::LoadHighScore(filepath, this);
}

HighScoreComponent::~HighScoreComponent()
{
	WriteHighScoreListToFile();
}

void HighScoreComponent::AddScore(int score, const std::string& name)
{
	m_HighScores.emplace_back(HighScoreStruct{ score,name });
	Sort();
}

void HighScoreComponent::WriteHighScoreListToFile()
{
	JsonHelper::SaveHighScore(m_Filepath, this);
}

void HighScoreComponent::Sort()
{
	std::sort(m_HighScores.begin(), m_HighScores.end(), [&](const HighScoreStruct& a, const HighScoreStruct& b)
		{
			return a.score > b.score;
		});
}
