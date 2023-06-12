#include "FireComponent.h"

#include "ServiceLocator.h"
#include "AudioManager.h"

void FireComponent::Initialize()
{
	ServiceLocator::GetAudio().PlaySound(2);
}

void FireComponent::Update()
{
}
