#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "EngineTime.h"
#include "GameObject.h"
#include "TextComponent.h"

void dae::FpsComponent::Update()
{
	float fps = 1.f / float(Time::GetInstance().GetElapsedSeconds());
	m_pGameObject->GetComponent<TextComponent>()->SetText(std::to_string(fps) + " FPS");
}
