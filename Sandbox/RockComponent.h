#pragma once
#include "BaseComponent.h"
namespace dae
{
	class TextureComponent;
}

class RockComponent final : public dae::BaseComponent
{
public:
	RockComponent() = default;
	RockComponent(const RockComponent&) = delete;
	RockComponent& operator=(const RockComponent&) = delete;
	RockComponent(RockComponent&&) = delete;
	RockComponent& operator=(RockComponent&&) = delete;
	~RockComponent() override = default;

protected:
	void Initialize() override;
	void Update() override;

	bool m_IsFalling{ false };
	float m_StartWobble{ 0 };
	float m_WobbleDuration{ 2.f };

	float m_SmallStartCrumble{ 0 };
	float m_SmallCrumbleDuration{ 1.f };
	int m_AnimationIndex{ 0 };
	bool m_IsCrumbling{ false };
	dae::TextureComponent* m_pTextureComponent{ nullptr };
};