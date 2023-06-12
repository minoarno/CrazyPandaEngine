#include "MiniginPCH.h"
#include "HighScoreComponent.h"

#include "JsonHelper.h"
#include "TextComponent.h"

#include "ScoreManager.h"

HighScoreComponent::HighScoreComponent(const std::string& filepath)
	: BaseComponent{ }
	, m_Filepath{ filepath }
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
	std::sort(m_HighScores.begin(), m_HighScores.end(), [](int a, int b) {
		return a > b;
		});

	UpdateText();
}

void HighScoreComponent::WriteHighScoreListToFile()
{
	JsonHelper::SaveHighScore(m_Filepath, this);
}

void HighScoreComponent::Initialize()
{
	m_pText = m_pGameObject->GetComponent<dae::TextComponent>();
}

void HighScoreComponent::Update()
{
	if (m_IsFirstFrame)
	{
		AddScore(ScoreManager::GetInstance().GetScore());
		ScoreManager::GetInstance().ResetScore();
		m_IsFirstFrame = false;
	}
}

void HighScoreComponent::UpdateText()
{
	std::string text{""};

	if (int(m_HighScores.size()) > 1)
	{
		text = "High Score: " + std::to_string(m_HighScores[0]);

		m_pText->SetText(text);
	}
}