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

void HighScoreComponent::AddScore(int score)
{
	m_HighScores.emplace_back( score );
	std::sort(m_HighScores.begin(), m_HighScores.end());;
}

void HighScoreComponent::WriteHighScoreListToFile()
{
	JsonHelper::SaveHighScore(m_Filepath, this);
}