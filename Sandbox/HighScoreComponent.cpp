#include "MiniginPCH.h"
#include "HighScoreComponent.h"

#include "JsonHelper.h"
#include "TextComponent.h"

#include "ScoreManager.h"
#include "ResourceManager.h"

HighScoreComponent::HighScoreComponent(const std::string& filepath)
	: BaseComponent{ }
	, m_Filepath{ filepath }
{
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
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	for (size_t i = 0; i < 10; i++)
	{
		auto pChild = m_pGameObject->AddChild(new dae::GameObject{});
		pChild->SetPosition({ 0,32 * i });
		m_pTexts.emplace_back(pChild->AddComponent(new dae::TextComponent{ font,"" }));
	}

	JsonHelper::LoadHighScore(m_Filepath, this);

	UpdateText();
}

void HighScoreComponent::Update()
{
	if (m_IsFirstFrame)
	{
		AddScore(ScoreManager::GetInstance().GetScore());
		ScoreManager::GetInstance().ResetScore();

		m_IsFirstFrame = false;
	}

	UpdateText();
}

void HighScoreComponent::UpdateText()
{
	int size = (int(m_HighScores.size()) < 10) ? int(m_HighScores.size()) : 10;
	
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
		{
			m_pTexts[i]->SetText("HighScore: " + std::to_string(m_HighScores[i]));
		}
		else
		{
			m_pTexts[i]->SetText("Score: " + std::to_string(m_HighScores[i]));
		}
	}
}