#pragma once
#include "Command.h"
#include "PlayerComponent.h"

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