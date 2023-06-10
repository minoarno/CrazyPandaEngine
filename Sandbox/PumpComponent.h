#pragma once
#include "BaseComponent.h"

class PumpComponent final : public dae::BaseComponent
{
public:
	PumpComponent() = default;
	PumpComponent(const PumpComponent&) = delete;
	PumpComponent& operator=(const PumpComponent&) = delete;
	PumpComponent(PumpComponent&&) = delete;
	PumpComponent& operator=(PumpComponent&&) = delete;
	~PumpComponent() override = default;

protected:
	void Initialize() override;
	void Update() override;

private:
	float m_LastPumpIncrement{};
	float m_PumpIncrementDuration{.25f};
};