#pragma once
#include "Singleton.h"
#include "EventSubject.h"
#include <deque>
#include <string>

class GameStateManager : public dae::Singleton<GameStateManager>, public dae::EventSubject
{
public:
	GameStateManager() = default;
	GameStateManager(const GameStateManager&) = delete;
	GameStateManager& operator=(const GameStateManager&) = delete;
	GameStateManager(GameStateManager&&) = delete;
	GameStateManager& operator=(GameStateManager&&) = delete;
	~GameStateManager() = default;

	void ResetEnemies();
	void OnEnemySpawn();
	void OnEnemyDead(); 

	void GoToEndScene();
	void AddLevelNames(const std::vector<std::string>& list) { m_NamesLevels = list; }

private:
	void CheckForNextScene();

	int m_AmountOfEnemies = 0;
	std::vector<std::string> m_NamesLevels{};
};
