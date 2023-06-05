#include "MiniginPCH.h"
#include "ContactListener.h"

#include "GameObject.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	Contact(contact, CollisionType::BeginContact);
}

void ContactListener::EndContact(b2Contact* contact)
{
	Contact(contact, CollisionType::EndContact);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold*)
{
	Contact(contact, CollisionType::PreSolve);
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse*)
{
	Contact(contact, CollisionType::PostSolve);
}

void ContactListener::Contact(b2Contact* contact, CollisionType collisionType)
{
	dae::GameObject* obj1 = static_cast<dae::GameObject*>(contact->GetFixtureA()->GetUserData());
	dae::GameObject* obj2 = static_cast<dae::GameObject*>(contact->GetFixtureB()->GetUserData());

	if (obj1 != nullptr && obj2 != nullptr)
	{
		obj1->Collision(contact->GetFixtureA(), contact->GetFixtureB(), contact, collisionType);
		obj2->Collision(contact->GetFixtureB(), contact->GetFixtureA(), contact, collisionType);
	}
}
