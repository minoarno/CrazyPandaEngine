#include "MiniginPCH.h"
#include "ScoreDisplay.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "ScoreObserver.h"
#include "Score.h"

ScoreDisplay::ScoreDisplay(PlayerComponent* pPlayerComponent)
	: BaseComponent{}
	, m_pPlayerComponent{pPlayerComponent}
{
}

ScoreDisplay::~ScoreDisplay()
{
	delete m_pScoreObserver;
	m_pScoreObserver = nullptr;
}

void ScoreDisplay::Initialize()
{
	dae::TextComponent* pText = new dae::TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pGameObject->AddComponent(pText);
	m_pScoreObserver = new ScoreObserver{ pText };
	m_pPlayerComponent->GetScore()->AddObserver(m_pScoreObserver);
	pText->SetText("Score: 0");
}
