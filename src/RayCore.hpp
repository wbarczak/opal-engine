#pragma once

#include "raylib.h"
#include "Core.hpp"

inline Vector2 toRay(Vec2 v)
{
	return Vector2{
		v.x,
		v.y
	};
}

inline Rectangle toRay(Rect r)
{
	return Rectangle
	{
		r.pos.x,
		r.pos.y,
		r.w,
		r.h
	};
}

inline Color toRay(Col c)
{
	return Color{
		c.r,
		c.g,
		c.b,
		c.a
	};
}

inline Vec2 toCore(Vector2 v)
{
	return Vec2{
		v.x,
		v.y
	};
}

inline Rect toCore(Rectangle r)
{
	return Rect
	{
		r.x,
		r.y,
		r.width,
		r.height
	};
}

inline Col toCore(Color c)
{
	return Col{
		c.r,
		c.g,
		c.b,
		c.a
	};
}