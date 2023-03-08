#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(const glm::vec3& pos = {0,0,0});

		[[nodiscard]] const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		[[nodiscard]] glm::vec3 GetWorldPosition()const;
		
		void SetLocalPosition(float x, float y, float z);
		void SetRotation(float angle);
		void Move(float x, float y, float z);
		[[nodiscard]] float GetRotation()const { return m_Angle; };
	private:
		mutable bool m_NeedUpdate = false;
		glm::vec3 m_LocalPosition;
		mutable glm::vec3 m_WorldPosition;
		float m_Angle{0};
	};
}
