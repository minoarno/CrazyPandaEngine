#pragma once
#include "BaseComponent.h"
#include "EventObserver.h"

namespace dae
{
	class TextComponent;
}

class Lives;
class LivesDisplay final : public dae::BaseComponent, public dae::EventObserver
{
public:
	LivesDisplay(Lives* pLivesComponent);
	LivesDisplay(const LivesDisplay&) = delete;
	LivesDisplay& operator=(const LivesDisplay&) = delete;
	LivesDisplay(LivesDisplay&&) = delete;
	LivesDisplay& operator=(LivesDisplay&&) = delete;
	~LivesDisplay() override = default;

	void Initialize() override;
	void OnNotify(dae::EventSubject* pEventSubject) override;
private:
	Lives* m_pLivesComponent = nullptr;
	dae::TextComponent* m_pTextComponent = nullptr;
};

