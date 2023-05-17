#include "MiniginPCH.h"
#include "ScoreObserver.h"

#include "Score.h"
#include "TextComponent.h"

ScoreObserver::ScoreObserver(dae::TextComponent* pTextComponent)
	:m_pTextComponent{ pTextComponent }
{
}

void ScoreObserver::SetTextComponent(dae::TextComponent* pTextComponent)
{
	m_pTextComponent = pTextComponent;
}

void ScoreObserver::OnNotify(dae::EventSubject* pEventSubject)
{
	Score* score = dynamic_cast<Score*>(pEventSubject);
	std::string temp = "Score: " + std::to_string(score->GetScore());
	m_pTextComponent->SetText(temp);
}
