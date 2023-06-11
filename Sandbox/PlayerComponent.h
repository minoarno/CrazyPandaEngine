#pragma once
#include "BaseComponent.h"

class Lives;
class PlayerComponent : public dae::BaseComponent
{
public:
	PlayerComponent(int amountOfLives);
	PlayerComponent(const PlayerComponent&) = delete;
	PlayerComponent& operator=(const PlayerComponent&) = delete;
	PlayerComponent(PlayerComponent&&) = delete;
	PlayerComponent& operator=(PlayerComponent&&) = delete;
	~PlayerComponent() override = default;

	void Dies();
	void AddScore(int score);

	[[nodiscard]] std::shared_ptr<Lives> GetLives() const {return  m_pLives;}
private:
	std::shared_ptr<Lives> m_pLives;
};