#pragma once
#include "BaseComponent.h"

class DigDugComponent final : public dae::BaseComponent
{
public:
	enum class CharacterDirection : int
	{
		Right = 0,
		Up = 1,
		Left = 2,
		Down = 3
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
	CharacterDirection GetDirection()const { return m_Direction; };
	void SetState(CharacterState state);
	CharacterState GetState()const { return m_State; };

protected:
	void Initialize() override;
	void Update() override;

	CharacterDirection m_Direction{};
	CharacterState m_State{};
};