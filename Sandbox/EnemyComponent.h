#pragma once
#include "BaseComponent.h"

class EnemyComponent : public dae::BaseComponent
{
public:
	enum class EnemyState
	{
		Walk,
		Ghost,
		Bloated,
		Die
	};

	EnemyComponent();
	EnemyComponent(const EnemyComponent&) = delete;
	EnemyComponent& operator=(const EnemyComponent&) = delete;
	EnemyComponent(EnemyComponent&&) = delete;
	EnemyComponent& operator=(EnemyComponent&&) = delete;
	~EnemyComponent() override = default;
protected:
	virtual void Initialize();

	virtual void Update();
};