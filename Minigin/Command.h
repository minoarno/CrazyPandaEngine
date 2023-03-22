#pragma once
#include <iostream>

class Command
{
public:
	Command() = default;
	Command(const Command& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(Command&& other) = delete;

	virtual ~Command() = default;
	virtual void Execute() const = 0;
};

class FireCommand final : public Command
{
public:
	FireCommand() = default;
	FireCommand(const FireCommand&) = delete;
	FireCommand& operator=(const FireCommand&) = delete;
	FireCommand(FireCommand&&) = delete;
	FireCommand& operator=(FireCommand&&) = delete;

	virtual ~FireCommand() = default;

	virtual void Execute() const
	{
		std::cout << "Fire\n";
	}
};

class DuckCommand final : public Command
{
public:
	DuckCommand() = default;
	DuckCommand(const DuckCommand&) = delete;
	DuckCommand& operator=(const DuckCommand&) = delete;
	DuckCommand(DuckCommand&&) = delete;
	DuckCommand& operator=(DuckCommand&&) = delete;

	virtual ~DuckCommand() = default;

	virtual void Execute() const
	{
		std::cout << "Duck\n";
	}
};

class JumpCommand final : public Command
{
public:
	JumpCommand() = default;
	JumpCommand(const JumpCommand&) = delete;
	JumpCommand& operator=(const JumpCommand&) = delete;
	JumpCommand(JumpCommand&&) = delete;
	JumpCommand& operator=(JumpCommand&&) = delete;

	virtual ~JumpCommand() = default;

	virtual void Execute() const
	{
		std::cout << "Jump\n";
	}
};

class FartCommand final : public Command
{
public:
	FartCommand() = default;
	FartCommand(const FartCommand&) = delete;
	FartCommand& operator=(const FartCommand&) = delete;
	FartCommand(FartCommand&&) = delete;
	FartCommand& operator=(FartCommand&&) = delete;

	virtual ~FartCommand() = default;

	virtual void Execute() const
	{
		std::cout << "Fart\n";
	}
};

