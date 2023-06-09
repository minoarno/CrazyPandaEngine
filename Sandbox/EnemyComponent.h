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
		Fire,
		Die
	};

	EnemyComponent();
	EnemyComponent(const EnemyComponent&) = delete;
	EnemyComponent& operator=(const EnemyComponent&) = delete;
	EnemyComponent(EnemyComponent&&) = delete;
	EnemyComponent& operator=(EnemyComponent&&) = delete;
	~EnemyComponent() override = default;

	void SetEnemyState(EnemyState newState);
	EnemyState GetEnemyState()const { return m_State; }
protected:
	virtual void Initialize();

	virtual void Update();

	EnemyState m_State;
	glm::vec2 m_Direction;
	float m_Speed{ 200.f };
};