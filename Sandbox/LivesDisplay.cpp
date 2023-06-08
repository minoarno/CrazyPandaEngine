#include "MiniginPCH.h"
#include "LivesDisplay.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "LiveObserver.h"
#include "Lives.h"
#include "PlayerComponent.h"

LivesDisplay::LivesDisplay(PlayerComponent* pPlayerComponent)
	: BaseComponent{}
	, m_pPlayerComponent{ pPlayerComponent }
{
}

LivesDisplay::~LivesDisplay()
{
	delete m_pLivesObserver;
	m_pLivesObserver = nullptr;
}

void LivesDisplay::Initialize()
{
	dae::TextComponent* pText = new dae::TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pGameObject->AddComponent(pText);
	m_pLivesObserver = new LiveObserver(pText);
	m_pPlayerComponent->GetLives()->AddObserver(m_pLivesObserver);
	pText->SetText("Lives: 5");
}
