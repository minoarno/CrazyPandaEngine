#pragma once
#include "EnemyComponent.h"
class FygarComponent : public EnemyComponent
{
public:
	FygarComponent();
	FygarComponent(const FygarComponent&) = delete;
	FygarComponent& operator=(const FygarComponent&) = delete;
	FygarComponent(FygarComponent&&) = delete;
	FygarComponent& operator=(FygarComponent&&) = delete;
	~FygarComponent() override = default;

protected:
	void Initialize() override;
	void UpdateTexture() override;

	void Update() override;

	float m_LastFireTime{};
	float m_FireCooldown{};
};