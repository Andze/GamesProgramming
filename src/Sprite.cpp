#include "Sprite.h"
//http://www.dreamincode.net/forums/topic/112191-beginning-sdl-part-3-a-spritedrawing-class/
//http://www.sdltutorials.com/sdl-animation

Sprite::Sprite(int xl, int yl, int wl, int hl, int x, int y, int w, int h) {
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Constructed(%p)", this);
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;

	Lrectangle.x = xl;
	Lrectangle.y = yl;
	Lrectangle.w = wl;
	Lrectangle.h = hl;
}

Sprite::Sprite(const Sprite& sprite) : rectangle(sprite.rectangle)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Constructed(%p) - Copied from(%p)", this, sprite);
}


Sprite::~Sprite()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Destructed(%p)", this);
}
