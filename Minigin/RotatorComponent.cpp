#include "MiniginPCH.h"
#include "RotatorComponent.h"

#include "EngineTime.h"

dae::RotatorComponent::RotatorComponent(float rotationSpeed, float distanceFromMiddle)
    : m_RotationSpeed{rotationSpeed}
    , m_Angle{}
    , m_DistanceFromMiddle{distanceFromMiddle}
{
}

void dae::RotatorComponent::Update()
{
    m_Angle += m_RotationSpeed * static_cast<float>(Time::GetInstance().GetElapsedSeconds());
    const float angle = m_Angle * static_cast<float>(M_PI) / 180.f;
    m_pGameObject->GetTransform()->SetLocalPosition(
        cos(angle) * m_DistanceFromMiddle,
        sin(angle) * m_DistanceFromMiddle,
        0);
}
