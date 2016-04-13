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

	SDL_Surface* Sprite::OnLoad(char* File)
{
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
		return NULL;
	}

	Surf_Return = SDL_ConvertSurfaceFormat(Surf_Temp,0,0);
	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

bool Sprite::Draw(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, int x2, int y2, int width, int height)
{
		if (ren == nullptr || tex == NULL) {
				return false;
		}

		SDL_Rect destR;

		destR.x = x;
		destR.y = x;
		destR.w = 100;
		destR.h = 100;

		SDL_Rect srcR;

		srcR.x = x2;
		srcR.y = y2;
		srcR.w = width;
		srcR.h = height;

		SDL_RenderCopy(ren, tex, &srcR, &destR);
		//(src, &srcR, dest, &destR);

		return true;
}
bool Sprite::Draw(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect* dest)
{
	SDL_RenderCopy(ren, tex, NULL, dest);
	return true;
}


Sprite::Sprite(const Sprite& sprite) : rectangle(sprite.rectangle)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Constructed(%p) - Copied from(%p)", this, sprite);
}


Sprite::~Sprite()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Destructed(%p)", this);
}
