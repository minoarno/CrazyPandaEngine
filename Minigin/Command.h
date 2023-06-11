#pragma once
#include <iostream>
#include "GameObject.h"
#include "EngineTime.h"
#include "Scene.h"
#include "SceneManager.h"

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
		, m_PrevLocalPos{ }
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

class LoadSceneCommand final : public Command
{
public:
	LoadSceneCommand(const std::string& nextSceneName)
		: m_NextSceneName{ nextSceneName }
	{
	}
	LoadSceneCommand(const LoadSceneCommand&) = delete;
	LoadSceneCommand& operator=(const LoadSceneCommand&) = delete;
	LoadSceneCommand(LoadSceneCommand&&) = delete;
	LoadSceneCommand& operator=(LoadSceneCommand&&) = delete;
	~LoadSceneCommand() override = default;

	virtual void Execute()
	{
		m_PrevSceneName = dae::SceneManager::GetInstance().GetActiveScene().GetSceneName();
		dae::SceneManager::GetInstance().LoadScene(m_NextSceneName);
	}

	virtual void Undo()
	{
		dae::SceneManager::GetInstance().LoadScene(m_PrevSceneName);
	}
private:
	std::string m_NextSceneName{};
	std::string m_PrevSceneName{};
};