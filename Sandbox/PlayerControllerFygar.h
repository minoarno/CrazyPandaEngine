#pragma once
#include "FygarComponent.h"

class PlayerControllerFygar final : public FygarComponent
{
public:
	PlayerControllerFygar() = default;
	PlayerControllerFygar(const PlayerControllerFygar&) = delete;
	PlayerControllerFygar& operator=(const PlayerControllerFygar&) = delete;
	PlayerControllerFygar(PlayerControllerFygar&&) = delete;
	PlayerControllerFygar& operator=(PlayerControllerFygar&&) = delete;
	~PlayerControllerFygar() override = default;

	void StartFire();
protected:
	void Update() override;
};