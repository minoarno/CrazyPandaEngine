#pragma once
#include "Box2D/Dynamics/b2WorldCallbacks.h"

class RayCastCallback : public b2RayCastCallback
{
public:
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

    dae::GameObject* m_pHitFixture;
    glm::vec2 m_Position;
    glm::vec2 m_Normal;
    float m_Fraction;
    std::string m_Tag;
};

