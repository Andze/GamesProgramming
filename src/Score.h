#pragma once
#ifndef Score_h
#define Score_h

#include "common.h"

class Score
{
public:
	Score();
	~Score();

	static TTF_Font* LoadFont(char* File, int size);

	static int LoadHighscore(char* File,int Score);

	static bool SaveHighScore(char* File,int Score, int HighScore);

	static SDL_Texture* LoadScore(TTF_Font* Font, int Score, int R, int G, int B, SDL_Renderer* Render);

	static bool DrawScore(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, int w, int h);
};

#endif /* end of include guard: */

