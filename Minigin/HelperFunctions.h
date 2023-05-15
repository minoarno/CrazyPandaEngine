#pragma once
#include "HelperStructs.h"

bool IsOverlapping(const Rectf& rect1, const Rectf& rect2);
bool IsOverlapping(const Rectf& rect, const glm::vec2& p);

//void SetColor(const Colorf& color);
//void DrawRect(const Rectf& rect);

glm::vec2 RotateVector(const glm::vec2& vector, float angleInRadians);