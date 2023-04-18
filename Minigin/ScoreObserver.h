#pragma once
#include "EventObserver.h"

namespace dae
{
	class TextComponent;	
}
class ScoreObserver final : public dae::EventObserver
{
public:
	ScoreObserver(dae::TextComponent* pTextComponent);
	ScoreObserver(const ScoreObserver& other) = delete;
	ScoreObserver& operator=(const ScoreObserver& other) = delete;
	ScoreObserver(ScoreObserver&& other) = delete;
	ScoreObserver& operator=(ScoreObserver&& other) = delete;
	~ScoreObserver() = default;

	void SetTextComponent(dae::TextComponent* pTextComponent);

	void OnNotify(dae::EventSubject* pEventSubject) override;
private:
	dae::TextComponent* m_pTextComponent = nullptr;
};

