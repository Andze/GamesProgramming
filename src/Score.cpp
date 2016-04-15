#include "Score.h"

TTF_Font* Text::LoadFont(char* File, int size)
{
	TTF_Font* font = TTF_OpenFont(File, size);
	if (font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

	}

	return font;
}

Score::Score()
{
}


Score::~Score()
{
}
