#pragma once
#include "GameStateManager.h"
#include "SceneManager.h"

void GameStateManager::ResetEnemies()
{
	m_AmountOfEnemies = 0;
}

void GameStateManager::OnEnemySpawn()
{
	m_AmountOfEnemies++;
}

void GameStateManager::OnEnemyDead()
{
	m_AmountOfEnemies--;
	if (m_AmountOfEnemies == 0)
	{
		CheckForNextScene();
	}
}

void GameStateManager::GoToEndScene()
{
	dae::SceneManager::GetInstance().LoadScene("HighScore");
}

void GameStateManager::CheckForNextScene()
{
	if (m_NamesLevels.size() == 0)
	{
		GoToEndScene();
		return;
	}
	
	dae::SceneManager::GetInstance().LoadScene(m_NamesLevels[0]);
	m_NamesLevels.pop_front();
}