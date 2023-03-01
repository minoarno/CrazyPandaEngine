#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "EngineTime.h"
#include "GameObject.h"
#include "TextComponent.h"

void dae::FpsComponent::Initialize()
{
	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
}

void dae::FpsComponent::Update()
{
	if (startTime + cooldown < Time::GetInstance().GetTotalSeconds())
	{
		int fps = static_cast<int>(round(1.f / float(Time::GetInstance().GetElapsedSeconds())));
		m_pTextComponent->SetText(std::to_string(fps) + " FPS");
		startTime = Time::GetInstance().GetTotalSeconds();
	}
}
