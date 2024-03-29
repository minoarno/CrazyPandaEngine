#include "MiniginPCH.h"
#include "RigidBody.h"

#include "Scene.h"
#include "Box2D.h"

RigidBody::RigidBody(bool isStatic)
	: BaseComponent{}
{
	m_BodyDef.type = (isStatic) ? b2_staticBody : b2_dynamicBody;
}

RigidBody::~RigidBody()
{
	b2World* pWorld = m_pGameObject->GetScene()->GetWorld();
	if (pWorld != nullptr)
	{
		if (pWorld->IsLocked())
		{
			Log::CoreError("Removal while physics step is active");
		}
		pWorld->DestroyBody(m_pBody);
	}
}

b2Fixture* RigidBody::AddCollider(const b2FixtureDef& fixtureDef)
{
	return m_pBody->CreateFixture(&fixtureDef);
}

void RigidBody::Move(const float x, const float y)
{
	auto linearVelocity = m_pBody->GetLinearVelocity();
	linearVelocity.x += x;
	linearVelocity.y += y;
	m_pBody->SetLinearVelocity(linearVelocity);
}

void RigidBody::SetEnabled(bool value)
{
	m_pBody->SetActive(value);
	m_pBody->SetLinearVelocity({ 0,0 });
}

void RigidBody::ResetVelocity()
{
	m_pBody->SetLinearVelocity({ 0,0 });
}

void RigidBody::SetGravityScale(float scale)
{
	m_pBody->SetGravityScale(scale);
}

void RigidBody::Initialize()
{
	m_BodyDef.userData = m_pGameObject;

	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
	m_BodyDef.position = {pos.x, pos.y};
	m_BodyDef.fixedRotation = true;

	auto pScene = m_pGameObject->GetScene();
	auto pWorld = pScene->GetWorld();
	m_pBody = pWorld->CreateBody(&m_BodyDef);
}

void RigidBody::Update()
{
	if (m_pBody == nullptr) return;

	auto worldPos = (m_pGameObject->GetParent() != nullptr)? m_pGameObject->GetParent()->GetTransform()->GetWorldPosition() : glm::vec3{0, 0, 0};
	auto pos = m_pBody->GetPosition();
	m_pGameObject->SetPosition(pos.x - worldPos.x, pos.y - worldPos.y, 0);
}
