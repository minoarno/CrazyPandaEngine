#pragma once
#include "BaseComponent.h"

class Lives;
class Score;
class PlayerComponent : public dae::BaseComponent
{
public:
	PlayerComponent(int amountOfLives);
	PlayerComponent(const PlayerComponent&) = delete;
	PlayerComponent& operator=(const PlayerComponent&) = delete;
	PlayerComponent(PlayerComponent&&) = delete;
	PlayerComponent& operator=(PlayerComponent&&) = delete;
	~PlayerComponent() override;

	void Dies();
	void AddScore(int score);

	[[nodiscard]] Lives* GetLives() const {return  m_pLives;}
	[[nodiscard]] Score* GetScore() const {return  m_pScore;}
private:
	Lives* m_pLives;
	Score* m_pScore;
};