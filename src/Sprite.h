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

	static SDL_Surface* OnLoad(char* File);
	
	static bool Draw(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, int x2, int y2, int width, int height);
	static bool Draw(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect* dest);
	~Sprite();
};

#endif /* end of include guard: */

