#include "MiniginPCH.h"
#include "BoxCollider.h"
#include "Box2D.h"
#include "Box2D/Common/b2Draw.h"
#include "Renderer.h"

BoxCollider::BoxCollider(const glm::vec2& dim, const glm::vec2& center)
	:ColliderComponent{}
{
	m_Shape = b2PolygonShape();
	m_Shape.SetAsBox(dim.x * .5f, dim.y * .5f, b2Vec2(center.x, center.y), 0.f);
	m_Filter.maskBits = 0xFFFF;
	m_FixtureDef.density = 1.0f;
}

void BoxCollider::Initialize()
{
	ColliderComponent::Initialize();
	m_pFixture->SetSensor(false);
}