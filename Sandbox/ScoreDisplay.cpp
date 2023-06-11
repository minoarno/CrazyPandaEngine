#include "MiniginPCH.h"
#include "ScoreDisplay.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "ScoreManager.h"

ScoreDisplay::ScoreDisplay(PlayerComponent* pPlayerComponent)
	: BaseComponent{}
	, m_pPlayerComponent{pPlayerComponent}
{
}

void ScoreDisplay::Initialize()
{
	dae::TextComponent* pText = new dae::TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pGameObject->AddComponent(pText);
	m_pTextComponent = pText;
	ScoreManager::GetInstance().AddObserver(this);
	pText->SetText("Score: 0");
}

void ScoreDisplay::OnNotify(dae::EventSubject* pEventSubject)
{
	ScoreManager* score = reinterpret_cast<ScoreManager*>(pEventSubject);
	std::string temp = "Score: " + std::to_string(score->GetScore());
	m_pTextComponent->SetText(temp);
}