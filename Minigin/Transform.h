#pragma once

#pragma warning(push)
#pragma warning(disable : 4201)
#pragma warning(disable : 26495)
#include <glm/glm.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform(const glm::vec3& pos = {0,0,0});

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		glm::vec3 GetWorldPosition() const;
		
		void SetLocalPosition(float x, float y, float z);
		void SetRotation(float angle);
		void Move(float x, float y, float z);
		float GetRotation()const { return m_Angle; };
	private:
		glm::vec3 m_LocalPosition;
		float m_Angle{0};
	};
}
