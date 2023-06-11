#pragma once
#include "BaseComponent.h"
#include "DigDugComponent.h"

class EnemyComponent;
class PumpComponent final : public dae::BaseComponent
{
public:
	PumpComponent(DigDugComponent::CharacterDirection direction);
	PumpComponent(const PumpComponent&) = delete;
	PumpComponent& operator=(const PumpComponent&) = delete;
	PumpComponent(PumpComponent&&) = delete;
	PumpComponent& operator=(PumpComponent&&) = delete;
	~PumpComponent() override = default;

	void AttachToEnemy(EnemyComponent* pEnemy);
	void DetachEnemy();

	DigDugComponent::CharacterDirection GetCharacterDirection()const { return m_CharacterDirection; };
protected:
	void Initialize() override;
	void Update() override;

private:
	float m_LastPumpIncrement{};
	float m_StartPump{};
	float m_PumpIncrementDuration{.25f};
	float m_PumpTotal{2.f};

	EnemyComponent* m_pEnemy{ nullptr };
	DigDugComponent::CharacterDirection m_CharacterDirection{};
};