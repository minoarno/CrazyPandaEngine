#pragma once

struct Rectf
{
	float x;
	float y;
	float w;
	float h;
};

struct Colorf
{
	float r;
	float g;
	float b;
};

struct Vector2f
{
	float x;
	float y;


	Vector2f()
		:x{0}
		,y{0}
	{
	}
	Vector2f(float x, float y)
		: x{x}
		, y{y}
	{
	}
	Vector2f(int x, int y)
		: x{ static_cast<float>(x) }
		, y{ static_cast<float>(y) }
	{
	}
};
