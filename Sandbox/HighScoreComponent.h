#pragma once
#include "BaseComponent.h"

class HighScoreComponent : public dae::BaseComponent
{
public:
	HighScoreComponent(const std::string& filepath);
	HighScoreComponent(const HighScoreComponent&) = delete;
	HighScoreComponent& operator=(const HighScoreComponent&) = delete;
	HighScoreComponent(HighScoreComponent&&) = delete;
	HighScoreComponent& operator=(HighScoreComponent&&) = delete;
	~HighScoreComponent();

	void AddScore(int score);

	void WriteHighScoreListToFile();
	std::vector<int> GetHighScores()const { return m_HighScores; }
protected:
	std::vector<int> m_HighScores;
	std::string m_Filepath;
};