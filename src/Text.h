#pragma once
#ifndef Text_h
#define Text_h

#include "common.h"


class Text
{
public:
	SDL_Rect rectangle;
	Text(int x, int y, int w, int h);
	Text(const Text& sprite);
	~Text();

	static bool DrawText(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, int w, int h);

	static SDL_Texture* LoadText(char* File, char *text, int size, int R, int G, int B, SDL_Renderer* Render);

};

#endif /* end of include guard: */
