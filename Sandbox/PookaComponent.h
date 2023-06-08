#pragma once
#include "EnemyComponent.h"

class PookaComponent : public EnemyComponent
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