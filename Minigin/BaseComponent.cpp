#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

void dae::BaseComponent::BaseInitialize()
{
	if (m_IsInitialized) return;
	Initialize();
	m_IsInitialized = true;
}
