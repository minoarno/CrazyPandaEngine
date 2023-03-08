#pragma once
#include "BaseComponent.h"

namespace dae
{
    class RotatorComponent final : public BaseComponent
    {
    public:
        RotatorComponent(float rotationSpeed, float distanceFromMiddle);
        RotatorComponent(const RotatorComponent& other) = default;
        RotatorComponent& operator=(const RotatorComponent& other) = default;
        RotatorComponent(RotatorComponent&& other) = default;
        RotatorComponent& operator=(RotatorComponent&& other) = default;
        ~RotatorComponent() override = default;

        void Update() override;

        void SetRotationSpeed(const float rotationSpeed){ m_RotationSpeed = rotationSpeed; }
        void SetDistanceFromMiddle(const float distance){ m_DistanceFromMiddle = distance; }
    private:
        float m_RotationSpeed;
        float m_Angle;
        float m_DistanceFromMiddle;
    };   
}
