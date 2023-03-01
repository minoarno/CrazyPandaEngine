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
		virtual ~FpsComponent() = default;
	protected:
		virtual void Update() override;

	private:
		double startTime = 0.f;
		double cooldown = 1.f;
	};

}

