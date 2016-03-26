#include "Text.h"

Text::Text(char a, int x, int y, int w, int h)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Text Constructed(%p)", this);
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
}

Text::Text(const Text& Text) : rectangle(Text.rectangle)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Text Constructed(%p) - Copied from(%p)", this, Text);
}

Text::~Text()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sounds Loaded");
}
