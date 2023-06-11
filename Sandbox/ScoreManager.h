#pragma once
#include "Singleton.h"
#include "EventSubject.h"

class ScoreManager : public dae::Singleton<ScoreManager>, public dae::EventSubject
{
public:
	ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;
	ScoreManager(ScoreManager&&) = delete;
	ScoreManager& operator=(ScoreManager&&) = delete;
	~ScoreManager() = default;

	void ResetScore();
	void IncreaseScore(int amount);
	int GetScore()const;
	void SetHeightLevels(const std::vector<float>& heights);
	int GetHeightMultiplier(float yLevel);
private:
	friend class dae::Singleton<ScoreManager>;
	int m_Score = 0;
	std::vector<float> m_Heights;
};

