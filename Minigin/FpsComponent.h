#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	class FpsComponent : public dae::BaseComponent
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
	};

}

