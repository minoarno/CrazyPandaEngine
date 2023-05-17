#pragma once
#include "EventObserver.h"

namespace dae
{
	class TextComponent;
}
class LiveObserver final : public dae::EventObserver
{
public:
	LiveObserver(dae::TextComponent* pTextComponent);
	LiveObserver(const LiveObserver& other) = delete;
	LiveObserver& operator=(const LiveObserver& other) = delete;
	LiveObserver(LiveObserver&& other) = delete;
	LiveObserver& operator=(LiveObserver&& other) = delete;
	~LiveObserver() override = default;

	void SetTextComponent(dae::TextComponent* pTextComponent);

	void OnNotify(dae::EventSubject* pEventSubject) override;
private:
	dae::TextComponent* m_pTextComponent = nullptr;
};
