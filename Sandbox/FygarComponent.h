#pragma once
#include "EnemyComponent.h"
#include "PumpComponent.h"

class FygarComponent : public EnemyComponent
{
public:
	FygarComponent();
	FygarComponent(const FygarComponent&) = delete;
	FygarComponent& operator=(const FygarComponent&) = delete;
	FygarComponent(FygarComponent&&) = delete;
	FygarComponent& operator=(FygarComponent&&) = delete;
	virtual ~FygarComponent() override = default;

	void SetPump(PumpComponent* pPump) { m_pPump = pPump; };
protected:
	void UpdateTexture() override;

	void AddScore() override;

	void Fire() override;

	float m_LastFireTime{};
	float m_FireCooldown{};

	PumpComponent* m_pPump{ nullptr };
};