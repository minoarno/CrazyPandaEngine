#pragma once
#include "BaseComponent.h"

class HighScoreComponent : public dae::BaseComponent
{
public:
	HighScoreComponent();
	HighScoreComponent(const HighScoreComponent&) = delete;
	HighScoreComponent& operator=(const HighScoreComponent&) = delete;
	HighScoreComponent(HighScoreComponent&&) = delete;
	HighScoreComponent& operator=(HighScoreComponent&&) = delete;
	~HighScoreComponent();
};