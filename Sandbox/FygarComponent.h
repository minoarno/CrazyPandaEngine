#pragma once
#include "BaseComponent.h"
class FygarComponent : public dae::BaseComponent
{
public:
	FygarComponent();
	FygarComponent(const FygarComponent&) = delete;
	FygarComponent& operator=(const FygarComponent&) = delete;
	FygarComponent(FygarComponent&&) = delete;
	FygarComponent& operator=(FygarComponent&&) = delete;
	~FygarComponent() override = default;

protected:
	void Initialize() override;
};