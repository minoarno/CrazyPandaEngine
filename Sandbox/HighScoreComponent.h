#pragma once
#include "BaseComponent.h"
namespace dae
{
	class TextComponent;
}

class HighScoreComponent final : public dae::BaseComponent
{
public:
	HighScoreComponent(const std::string& filepath, dae::TextComponent pText);
	HighScoreComponent(const HighScoreComponent&) = delete;
	HighScoreComponent& operator=(const HighScoreComponent&) = delete;
	HighScoreComponent(HighScoreComponent&&) = delete;
	HighScoreComponent& operator=(HighScoreComponent&&) = delete;
	~HighScoreComponent() override;

	void AddScore(int score);

	void WriteHighScoreListToFile();
	std::vector<int> GetHighScores()const { return m_HighScores; }
protected:
	void Update() override;

	void UpdateText();

	std::vector<int> m_HighScores;
	std::string m_Filepath;
	dae::TextComponent* m_pText{ nullptr };
	bool m_IsFirstFrame{ true };
};