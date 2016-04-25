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

	static SDL_Texture* OnLoad(char* File, SDL_Renderer* Render, int r, int g, int b);

	static SDL_Color SetColor(int R, int G, int B);

	static bool Transparency(SDL_Surface* Surface, SDL_Color Color);

	static bool Draw(SDL_Renderer* ren, SDL_Texture* tex, int xl, int yl, int wl, int hl, int x, int y, int w, int h);

	static bool Draw(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect* dest);
	~Sprite();
};

#endif /* end of include guard: */

