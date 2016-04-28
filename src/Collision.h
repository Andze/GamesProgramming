#pragma once
#ifndef Collision_h
#define Collision_h

#include "common.h"

class Collision
{
public:
	Collision();

	static bool RectCD(SDL_Rect *obj1, SDL_Rect *obj2);

	static bool Coords(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

	~Collision();
};

#endif /* end of include guard: */

