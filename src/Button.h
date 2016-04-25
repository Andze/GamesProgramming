#pragma once
#ifndef Button_h
#define Button_h

#include "common.h"

class Button
{
public:
	Button();

	static bool CreateButton(int x, int y, int w, int h, SDL_Event* e);

	~Button();
};

#endif /* end of include guard: */