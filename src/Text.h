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
};

#endif /* end of include guard: */
