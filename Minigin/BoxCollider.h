#pragma once
#include "HelperFunctions.h"
#include "ColliderComponent.h"

class BoxCollider final :  public ColliderComponent
{
public:
	BoxCollider(const glm::vec2& dim, const glm::vec2& center = {0,0});
	BoxCollider(const BoxCollider&) = delete;
	BoxCollider& operator=(const BoxCollider&) = delete;
	BoxCollider(BoxCollider&&) = delete;
	BoxCollider& operator=(BoxCollider&&) = delete;
	~BoxCollider() = default;

protected:
	virtual void Initialize() override;
};