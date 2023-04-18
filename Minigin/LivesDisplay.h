#pragma once
#include "BaseComponent.h"

class PlayerComponent;
class LiveObserver;
class LivesDisplay final : public dae::BaseComponent
{
public:
	LivesDisplay(PlayerComponent* pPlayerComponent);
	LivesDisplay(const LivesDisplay&) = delete;
	LivesDisplay& operator=(const LivesDisplay&) = delete;
	LivesDisplay(LivesDisplay&&) = delete;
	LivesDisplay& operator=(LivesDisplay&&) = delete;
	~LivesDisplay() override;

	void Initialize() override;

	[[nodiscard]] LiveObserver* GetLivesObserver() const { return m_pLivesObserver; };
private:
	LiveObserver* m_pLivesObserver = nullptr;
	PlayerComponent* m_pPlayerComponent = nullptr;
};

