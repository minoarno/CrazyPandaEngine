#include "MiniginPCH.h"
#include "b2DebugDraw.h"

#include "Renderer.h"
#include "HelperStructs.h"

void b2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::vector<glm::vec4> glmPoints;

	for (int32 i = 0; i < vertexCount; i++)
	{
		glmPoints.push_back({ (int)vertices[i].x,(int)vertices[i].y,0,1 });
	}

	int count = int(vertexCount) + 1;
	SDL_Point* points = new SDL_Point[count];
	for (int32 i = 0; i < vertexCount; i++)
	{
		points[i] = { (int)glmPoints[i].x,(int)glmPoints[i].y };
	}
	points[vertexCount] = { (int)glmPoints[0].x, (int)glmPoints[0].y };
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), Uint8(color.r * 255.0f), Uint8(color.g * 255.0f), Uint8(color.b * 255.0f), Uint8(color.a * 255.0f));
	SDL_RenderDrawLines(dae::Renderer::GetInstance().GetSDLRenderer(), points, vertexCount);

	delete[] points;
}

void b2DebugDraw::DrawSolidPolygon(const b2Vec2* , int32 , const b2Color& )
{
}

void b2DebugDraw::DrawCircle(const b2Vec2& , float32 , const b2Color& )
{
}

void b2DebugDraw::DrawSolidCircle(const b2Vec2& , float32 , const b2Vec2& , const b2Color& )
{
}

void b2DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), Uint8(color.r * 255.0f), Uint8(color.g * 255.0f), Uint8(color.b * 255.0f), Uint8(color.a * 255.0f));
	SDL_RenderDrawLine(dae::Renderer::GetInstance().GetSDLRenderer(), int(p1.x), (int)p1.y, int(p2.x), int(p2.y));
}

void b2DebugDraw::DrawTransform(const b2Transform& )
{
}

void b2DebugDraw::DrawPoint(const b2Vec2& , float32 , const b2Color& )
{
}
