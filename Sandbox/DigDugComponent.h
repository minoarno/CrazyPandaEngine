#pragma once
#include "BaseComponent.h"

class DigDugComponent final : public dae::BaseComponent
{
public:
	enum class CharacterDirection
	{
		Right,
		Up,
		Left,
		Down
	};

	enum class CharacterState
	{
		Walk,
		Pumping,
		Crushed,
		Die,
	};
	
	DigDugComponent();
	DigDugComponent(const DigDugComponent&) = delete;
	DigDugComponent& operator=(const DigDugComponent&) = delete;
	DigDugComponent(DigDugComponent&&) = delete;
	DigDugComponent& operator=(DigDugComponent&&) = delete;
	~DigDugComponent() override = default;

	void PumpAttack();
	void SetDirection(CharacterDirection direction);
	void SetState(CharacterState state);
protected:
	void Initialize() override;
	void Update() override;

	CharacterDirection m_CharacterDirection{};
	CharacterState m_CharacterState{};
};