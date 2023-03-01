#include "MiniginPCH.h"
#include "HelperFunctions.h"
#include "SDL_opengl.h"
#include <GL\GLU.h>

bool IsOverlapping(const Rectf& rect1, const Rectf& rect2)
{
	if (rect1.x > rect2.x + rect2.w || rect2.x > rect1.x + rect1.w) return false;

	if (rect1.y > rect2.y + rect2.h || rect2.y > rect1.y + rect1.h) return false;

	return true;
}

bool IsOverlapping(const Rectf& rect, const Vector2f& p)
{
	if (rect.x > p.x || p.x > rect.x + rect.w) return false;

	if (rect.y > p.y || p.y > rect.y + rect.h) return false;

	return true;
}

//void SetColor(const Colorf& color)
//{
//    glColor3f(GLfloat(color.r), GLfloat(color.g), GLfloat(color.b));
//}

//https://stackoverflow.com/questions/5877728/want-an-opengl-2d-example-vc-draw-a-rectangle
//void DrawRect(const Rectf& rect)
//{
//	glBegin(GL_POLYGON);
//	{
//		glVertex2i(int(rect.x), int(rect.y));
//		glVertex2i(int(rect.x + rect.w), int(rect.y));
//		glVertex2i(int(rect.x + rect.w), int(rect.y + rect.h));
//		glVertex2i(int(rect.x), int(rect.y + rect.h));
//	}
//	glEnd();
//}

Vector2f RotateVector(const Vector2f& vector, float angleInRadians)
{
	Vector2f result{};
	result.x = vector.x * cos(angleInRadians) - vector.y * sin(angleInRadians);
	result.y = vector.x * sin(angleInRadians) + vector.y * cos(angleInRadians);

	return result;
}
