#pragma once
#include "BaseComponent.h"
#include "box2d.h"

class RigidbodyComponent final : public dae::BaseComponent
{
public:
	RigidbodyComponent(bool isStatic);
    RigidbodyComponent(const RigidbodyComponent& other) = delete;
    RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
    RigidbodyComponent(RigidbodyComponent&& other) = delete;
    RigidbodyComponent& operator=(RigidbodyComponent&& other) = delete;
    ~RigidbodyComponent() override;

	b2Fixture* AddCollider(const b2FixtureDef& fixtureDef);
	void Move(const float x, const float y);
	b2Body* GetBody() { return m_pBody; };
protected:
	void Initialize() override;
	void Update() override;

private:
	b2Body* m_pBody{ nullptr };

	b2BodyDef m_BodyDef{};
};

