#pragma once
#include "BaseComponent.h"

class FireComponent : public dae::BaseComponent
{
public:
	FireComponent() = default;
	FireComponent(const FireComponent&) = delete;
	FireComponent& operator=(const FireComponent&) = delete;
	FireComponent(FireComponent&&) = delete;
	FireComponent& operator=(FireComponent&&) = delete;
	~FireComponent() override = default;

protected:
	void Initialize() override;
	void Update() override;

private:
	float m_LastFireIncrement{};
	float m_FireIncrementDuration{ .25f };
	float m_FireTotalDuration{ 1.f };
};