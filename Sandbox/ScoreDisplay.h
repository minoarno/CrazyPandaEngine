#pragma once
#include "BaseComponent.h"
#include "EventObserver.h"

namespace dae
{
	class TextComponent;
}

class ScoreDisplay final: public dae::BaseComponent, public dae::EventObserver
{
public:
	ScoreDisplay();
	ScoreDisplay(const ScoreDisplay&) = delete;
	ScoreDisplay& operator=(const ScoreDisplay&) = delete;
	ScoreDisplay(ScoreDisplay&&) = delete;
	ScoreDisplay& operator=(ScoreDisplay&&) = delete;
	~ScoreDisplay() override = default;

	void Initialize() override;
	void OnNotify(dae::EventSubject* pEventSubject) override;
private:
	dae::TextComponent* m_pTextComponent = nullptr;
};

