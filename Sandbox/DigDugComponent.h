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

	void SetRespawn(const glm::vec2& pos);
	void Respawn();
protected:
	void Initialize() override;
	void Update() override;

	void UpdateTexture();

	int m_WalkAnimations{ 2 };
	int m_GetCrushedAnimations{ 2 };
	int m_DeadAnimations{ 4 };
	int m_CurrentAnimationIndex{ 0 };
	float m_LastAnimationTime{};
	float m_AnimationDuration{ .5f };

	glm::vec2 m_RespawnPosition{};

	CharacterDirection m_Direction{};
	CharacterState m_State{};

	dae::TextureComponent* m_pTexture{};
};