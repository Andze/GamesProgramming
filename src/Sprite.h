#pragma once
#ifndef Sprite_h
#define Sprite_h

#include "common.h"

#endif /* end of include guard: */
class Sprite
{
public:
	SDL_Rect rectangle;
	Sprite(int x, int y, int w, int h);
	Sprite(const Sprite& sprite);
	~Sprite();
};

