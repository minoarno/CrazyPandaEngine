#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextureComponent;
}

class RigidBody;
class EnemyComponent : public dae::BaseComponent
{
public:
	enum class EnemyState
	{
		Walk,
		Ghost,
		Bloated,
		Crushed,
		Fire
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

	virtual void UpdateTexture();
	virtual void Walk();
	virtual void Ghost();
	virtual void Bloated();
	virtual void Crushed();
	virtual void Fire();

	EnemyState m_State;
	glm::vec2 m_Direction;
	float m_Speed{ 100.f };

	bool m_LooksRight{ true };
	int m_WalkAnimations{2};
	int m_GhosstAnimations{2};
	int m_BloathAnimations{4};
	int m_DeadAnimations{1};
	int m_CurrentAnimationIndex{0};
	float m_LastAnimationTime{};
	float m_AnimationDuration{.5f};

	dae::TextureComponent* m_pTexture{};
	RigidBody* m_pRigidBody{};
};