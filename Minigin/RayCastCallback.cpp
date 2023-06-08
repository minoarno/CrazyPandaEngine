#include "MiniginPCH.h"
#include "RayCastCallback.h"

float32 RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
    // Store fixture data or perform actions based on the collision
    this->m_pHitFixture = static_cast<dae::GameObject*>(fixture->GetUserData());
    this->m_Position = { point.x, point.y };
    this->m_Normal = { normal.x, normal.y };
    this->m_Fraction = fraction;
    return fraction;  // Return the fraction of the ray length to continue or stop casting
}
