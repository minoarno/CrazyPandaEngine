#pragma once
#include "BaseComponent.h"
#include "PlayerComponent.h"
#include "EventObserver.h"

namespace dae
{
	class TextComponent;
}

class ScoreDisplay final: public dae::BaseComponent, public dae::EventObserver
{
public:
	ScoreDisplay(PlayerComponent* pPlayerComponent);
	ScoreDisplay(const ScoreDisplay&) = delete;
	ScoreDisplay& operator=(const ScoreDisplay&) = delete;
	ScoreDisplay(ScoreDisplay&&) = delete;
	ScoreDisplay& operator=(ScoreDisplay&&) = delete;
	~ScoreDisplay() override = default;

	void Initialize() override;
	void OnNotify(dae::EventSubject* pEventSubject) override;
private:
	PlayerComponent* m_pPlayerComponent = nullptr;
	dae::TextComponent* m_pTextComponent = nullptr;
};

