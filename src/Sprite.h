#pragma once
#ifndef Sprite_h
#define Sprite_h

#include "common.h"

class Sprite
{
public:
	SDL_Rect Lrectangle;
	SDL_Rect rectangle;
	Sprite(int xl, int yl, int wl, int hl, int x, int y, int w, int h);
	Sprite(const Sprite& sprite);
	~Sprite();
};

#endif /* end of include guard: */

