#pragma once
#include "BaseComponent.h"
#include "PlayerComponent.h"

class Score;
class ScoreObserver;
class ScoreDisplay final: public dae::BaseComponent
{
public:
	ScoreDisplay(PlayerComponent* pPlayerComponent);
	ScoreDisplay(const ScoreDisplay&) = delete;
	ScoreDisplay& operator=(const ScoreDisplay&) = delete;
	ScoreDisplay(ScoreDisplay&&) = delete;
	ScoreDisplay& operator=(ScoreDisplay&&) = delete;
	~ScoreDisplay() override;

	void Initialize() override;

	[[nodiscard]] ScoreObserver* GetScoreObserver() const { return m_pScoreObserver; };
private:
	ScoreObserver* m_pScoreObserver = nullptr;
	PlayerComponent* m_pPlayerComponent = nullptr;
};

