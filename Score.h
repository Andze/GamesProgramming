#pragma once
#ifndef Score_h
#define Score_h

#include "common.h"

class Score
{
public:
	Score();

	static TTF_Font* LoadFont(char* File, int size);

	~Score();
};

#endif /* end of include guard: */

