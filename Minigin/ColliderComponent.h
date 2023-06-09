#pragma once
#include "BaseComponent.h"
#include "Box2D.h"

struct b2Filter;
class b2PolygonShape;
class b2Fixture;
class ColliderComponent : public dae::BaseComponent
{
public:
	ColliderComponent();
	ColliderComponent(const ColliderComponent&) = delete;
	ColliderComponent& operator=(const ColliderComponent&) = delete;
	ColliderComponent(ColliderComponent&&) = delete;
	ColliderComponent& operator=(ColliderComponent&&) = delete;
	virtual ~ColliderComponent() = default;

	void SetIsTrigger(bool value);
protected:
	virtual void Initialize() override;

	b2PolygonShape m_Shape{};

	b2Fixture* m_pFixture{ nullptr };
	b2Filter m_Filter;

	b2FixtureDef m_FixtureDef{};
};