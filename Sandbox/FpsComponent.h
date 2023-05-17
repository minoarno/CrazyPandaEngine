#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	class FpsComponent final : public dae::BaseComponent
	{
	public:
		FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = default;
		FpsComponent& operator=(const FpsComponent& other) = default;
		FpsComponent(FpsComponent&& other) = default;
		FpsComponent& operator=(FpsComponent&& other) = default;
		~FpsComponent() override = default;
	protected:
		void Initialize() override;
		void Update() override;

	private:
		double m_StartTime = 0.f;
		double m_Cooldown = 1.f;

		TextComponent* m_pTextComponent{};
	};

}

