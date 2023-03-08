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
	if (m_StartTime + m_Cooldown < Time::GetInstance().GetTotalSeconds())
	{
		const int fps = static_cast<int>(round(1.f / static_cast<float>(Time::GetInstance().GetElapsedSeconds())));
		m_pTextComponent->SetText(std::to_string(fps) + " FPS");
		m_StartTime = Time::GetInstance().GetTotalSeconds();
	}
}
