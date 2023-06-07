#pragma once
#include "BaseComponent.h"

class DigDugComponent : public dae::BaseComponent
{
public:
	DigDugComponent();
	DigDugComponent(const DigDugComponent&) = delete;
	DigDugComponent& operator=(const DigDugComponent&) = delete;
	DigDugComponent(DigDugComponent&&) = delete;
	DigDugComponent& operator=(DigDugComponent&&) = delete;
	~DigDugComponent() override = default;
protected:
	
};