#pragma once
#include <iostream>
#include "GameObject.h"
#include "EngineTime.h"
#include "PlayerComponent.h"

class Command
{
public:
	Command() = default;
	Command(const Command& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(Command&& other) = delete;

	virtual ~Command() = default;
	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

class MoveCommand final : public Command
{
public:
	MoveCommand(dae::GameObject* pGameobject, const glm::fvec3& dir)
		: Command{}
		, m_Direction{ dir }
		, m_pGameObject{ pGameobject }
	{

	}
	MoveCommand(const MoveCommand&) = delete;
	MoveCommand& operator=(const MoveCommand&) = delete;
	MoveCommand(MoveCommand&&) = delete;
	MoveCommand& operator=(MoveCommand&&) = delete;

	~MoveCommand() override = default;

	virtual void Execute() 
	{
		m_PrevLocalPos = m_pGameObject->GetTransform()->GetLocalPosition();
		m_pGameObject->GetTransform()->Move(m_Direction * static_cast<float>(Time::GetInstance().GetElapsedSeconds()));
	}

	virtual void Undo()
	{
		m_pGameObject->GetTransform()->SetLocalPosition(m_PrevLocalPos.x,m_PrevLocalPos.y,m_PrevLocalPos.z);
	}
private:
	glm::fvec3 m_Direction;
	glm::fvec3 m_PrevLocalPos;
	dae::GameObject* m_pGameObject;
};

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