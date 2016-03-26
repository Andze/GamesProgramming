#pragma once
#ifndef Text_h
#define Text_h

#include "common.h"

#endif /* end of include guard: */
class Text
{
public:
	SDL_Rect rectangle;
	Text(char a, int x, int y, int w, int h);
	Text(const Text& sprite);
	~Text();
};

