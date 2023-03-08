#include "MiniginPCH.h"
#include "RotatorComponent.h"

#include "EngineTime.h"
#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(float rotationSpeed, float distanceFromMiddle)
    : m_RotationSpeed{rotationSpeed}
    , m_Angle{}
    , m_DistanceFromMiddle{distanceFromMiddle}
{
}

void dae::RotatorComponent::Update()
{
    m_Angle += m_RotationSpeed * Time::GetInstance().GetElapsedSeconds();
    float angle = m_Angle * M_PI / 180;
    m_pGameObject->GetTransform()->SetLocalPosition(cos(angle)*m_DistanceFromMiddle,sin(angle)*m_DistanceFromMiddle,0);
}
