#pragma once
#include "Command.h"
#include "PlayerComponent.h"
#include "DigDugComponent.h"
#include "Scene.h"

class DieCommand final : public Command
{
public:
	DieCommand(PlayerComponent* pPlayerComponent)
		: Command{}
		, m_pPlayerComponent{ pPlayerComponent }
	{
	}

	~DieCommand() override = default;

	void Execute() override
	{
		m_pPlayerComponent->Dies();
	}

	void Undo() override {}
private:
	PlayerComponent* m_pPlayerComponent;
};

class ScoreIncrementCommand final : public Command
{
public:
	ScoreIncrementCommand(PlayerComponent* pPlayerComponent)
		: Command{}
		, m_pPlayerComponent{ pPlayerComponent }
	{
	}

	ScoreIncrementCommand(const ScoreIncrementCommand&) = delete;
	ScoreIncrementCommand& operator=(const ScoreIncrementCommand&) = delete;
	ScoreIncrementCommand(ScoreIncrementCommand&&) = delete;
	ScoreIncrementCommand& operator=(ScoreIncrementCommand&&) = delete;
	~ScoreIncrementCommand() override = default;

	void Execute() override
	{
		m_pPlayerComponent->AddScore(50);
	}

	void Undo() override {}
private:
	PlayerComponent* m_pPlayerComponent;
};

class DigDugMoveCommand final : public Command
{
public:
	DigDugMoveCommand(dae::GameObject* pGameobject, const glm::fvec3& dir, DigDugComponent::CharacterDirection direction)
		: Command{}
		, m_Direction{ dir }
		, m_pGameObject{ pGameobject }
		, m_CharacterDirection{ direction }
	{
		m_pRigidBody = m_pGameObject->GetComponent<RigidBody>();
		m_pDigDug = m_pGameObject->GetComponent<DigDugComponent>();
	}
	DigDugMoveCommand(const DigDugMoveCommand&) = delete;
	DigDugMoveCommand& operator=(const DigDugMoveCommand&) = delete;
	DigDugMoveCommand(DigDugMoveCommand&&) = delete;
	DigDugMoveCommand& operator=(DigDugMoveCommand&&) = delete;

	~DigDugMoveCommand() override = default;

	virtual void Execute()
	{
		auto direction = m_Direction * (static_cast<float>(Time::GetInstance().GetElapsedSeconds()));
		m_pRigidBody->ResetVelocity();
		m_pRigidBody->Move(direction.x, direction.y);

		RayCastCallback hit{};
		hit.m_Tags = { "Level" };
		glm::vec2 pos = m_pGameObject->GetTransform()->GetWorldPosition() + glm::vec3{ 8 };
		float distance = 10.f;
		if (m_pGameObject->GetScene()->RayCast(hit, pos, glm::normalize(m_Direction) * glm::vec2{distance}))
		{
			m_pGameObject->GetScene()->Remove(hit.m_pHitFixture);
		}
		m_pDigDug->SetDirection(m_CharacterDirection);
	}
	
	virtual void Undo()	{}

private:
	glm::vec2 m_Direction;
	dae::GameObject* m_pGameObject;
	DigDugComponent::CharacterDirection m_CharacterDirection;
	RigidBody* m_pRigidBody;
	DigDugComponent* m_pDigDug;
};

class DigDugPumpCommand final : public Command
{
public:
	DigDugPumpCommand(DigDugComponent* pDigDug)
		: Command{}
		, m_pDigDugComponent{ pDigDug}
	{

	}
	DigDugPumpCommand(const DigDugPumpCommand&) = delete;
	DigDugPumpCommand& operator=(const DigDugPumpCommand&) = delete;
	DigDugPumpCommand(DigDugPumpCommand&&) = delete;
	DigDugPumpCommand& operator=(DigDugPumpCommand&&) = delete;

	~DigDugPumpCommand() override = default;

	virtual void Execute()
	{
		m_pDigDugComponent->PumpAttack();
	}

	virtual void Undo()
	{
	}
private:
	DigDugComponent* m_pDigDugComponent;
};