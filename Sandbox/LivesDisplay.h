#pragma once
#include "BaseComponent.h"
#include "EventObserver.h"

namespace dae
{
	class TextComponent;
}

class PlayerComponent;
class LivesDisplay final : public dae::BaseComponent, public dae::EventObserver
{
public:
	LivesDisplay(PlayerComponent* pPlayerComponent);
	LivesDisplay(const LivesDisplay&) = delete;
	LivesDisplay& operator=(const LivesDisplay&) = delete;
	LivesDisplay(LivesDisplay&&) = delete;
	LivesDisplay& operator=(LivesDisplay&&) = delete;
	~LivesDisplay() override = default;

	void Initialize() override;
	void OnNotify(dae::EventSubject* pEventSubject) override;
private:
	PlayerComponent* m_pPlayerComponent = nullptr;
	dae::TextComponent* m_pTextComponent = nullptr;
};

