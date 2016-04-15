#pragma once
#ifndef Score_h
#define Score_h

#include "common.h"

class Score
{
public:
	Score();

	static TTF_Font* LoadFont(char* File, int size);

	static SDL_Texture* loadScore(TTF_Font* Font, int Score, int R, int G, int B, SDL_Renderer* Render);

	~Score();
};

#endif /* end of include guard: */

