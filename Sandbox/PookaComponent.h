#pragma once
#include "BaseComponent.h"

class PookaComponent : public dae::BaseComponent
{
public:
	PookaComponent();
	PookaComponent(const PookaComponent&) = delete;
	PookaComponent& operator=(const PookaComponent&) = delete;
	PookaComponent(PookaComponent&&) = delete;
	PookaComponent& operator=(PookaComponent&&) = delete;
	~PookaComponent() override = default;
protected:
	void Initialize() override;
};