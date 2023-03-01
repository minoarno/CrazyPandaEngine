#pragma once
#include "HelperStructs.h"

bool IsOverlapping(const Rectf& rect1, const Rectf& rect2);
bool IsOverlapping(const Rectf& rect, const Vector2f& p);

//void SetColor(const Colorf& color);
//void DrawRect(const Rectf& rect);

Vector2f RotateVector(const Vector2f& vector, float angleInRadians);