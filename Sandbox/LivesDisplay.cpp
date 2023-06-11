#include "MiniginPCH.h"
#include "LivesDisplay.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "Lives.h"
#include "PlayerComponent.h"

LivesDisplay::LivesDisplay(PlayerComponent* pPlayerComponent)
	: BaseComponent{}
	, m_pPlayerComponent{ pPlayerComponent }
{
}

void LivesDisplay::Initialize()
{
	dae::TextComponent* pText = new dae::TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pGameObject->AddComponent(pText);
	m_pTextComponent = pText;
	m_pPlayerComponent->GetLives()->AddObserver(this);
	pText->SetText("Lives: 5");
}

void LivesDisplay::OnNotify(dae::EventSubject* pEventSubject)
{
	Lives* lives = reinterpret_cast<Lives*>(pEventSubject);
	std::string temp = "Lives: " + std::to_string(lives->GetLives());
	m_pTextComponent->SetText(temp);
}
