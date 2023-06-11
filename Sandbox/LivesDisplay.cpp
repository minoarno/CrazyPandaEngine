#include "MiniginPCH.h"
#include "LivesDisplay.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "Lives.h"
#include "PlayerComponent.h"

LivesDisplay::LivesDisplay(Lives* pLivesComponent)
	: BaseComponent{}
	, m_pLivesComponent{ pLivesComponent }
{
}

void LivesDisplay::Initialize()
{
	dae::TextComponent* pText = new dae::TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pGameObject->AddComponent(pText);
	m_pTextComponent = pText;
	m_pLivesComponent->AddObserver(this);
	pText->SetText("Lives: " + std::to_string(m_pLivesComponent->GetLives()));
}

void LivesDisplay::OnNotify(dae::EventSubject* pEventSubject)
{
	Lives* lives = dynamic_cast<Lives*>(pEventSubject);
	std::string temp = "Lives: " + std::to_string(lives->GetLives());
	m_pTextComponent->SetText(temp);
}
