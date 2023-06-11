#pragma once
#include "BaseComponent.h"

struct HighScoreStruct
{
	int score;
	std::string name;
};

class HighScoreComponent : public dae::BaseComponent
{
public:
	HighScoreComponent(const std::string& filepath);
	HighScoreComponent(const HighScoreComponent&) = delete;
	HighScoreComponent& operator=(const HighScoreComponent&) = delete;
	HighScoreComponent(HighScoreComponent&&) = delete;
	HighScoreComponent& operator=(HighScoreComponent&&) = delete;
	~HighScoreComponent();

	void AddScore(int score, const std::string& name);

	void WriteHighScoreListToFile();
	std::vector<HighScoreStruct> GetHighScores()const { return m_HighScores; }
protected:
	std::vector<HighScoreStruct> m_HighScores;
	std::string m_Filepath;

	void Sort();
};