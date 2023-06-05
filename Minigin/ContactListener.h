#pragma once
#include "Box2D.h"

enum class CollisionType;
class ContactListener final : public b2ContactListener
{
public:
	ContactListener() = default;
	ContactListener(const ContactListener&) = delete;
	ContactListener& operator=(const ContactListener&) = delete;
	ContactListener(ContactListener&&) = delete;
	ContactListener& operator=(ContactListener&&) = delete;
	~ContactListener() = default;

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
	void Contact(b2Contact* contact, CollisionType collisionType);
};
