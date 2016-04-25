#include "Sprite.h"

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

SDL_Color Sprite::SetColor(int R, int G, int B)
{
	SDL_Color Color;

	Color.r = R;
	Color.g = G;
	Color.b = B;

	return Color;
};

bool Sprite::Transparency(SDL_Surface* Surface, SDL_Color Color)
{
	SDL_SetColorKey(Surface, SDL_TRUE, SDL_MapRGB(Surface->format, Color.r, Color.g, Color.b));

	return true;
};

	SDL_Texture* Sprite::OnLoad(char* File, SDL_Renderer* Render,int r,int g,int b)
{
	SDL_Surface* Surf_Temp = nullptr;
	SDL_Texture* Tex_Return = nullptr;

	Surf_Temp =  IMG_Load(File);

	Transparency(Surf_Temp, SetColor(r, g, b));

	if (Surf_Temp == nullptr) {
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
	}
	
	Tex_Return = SDL_CreateTextureFromSurface(Render, Surf_Temp);

	SDL_FreeSurface(Surf_Temp);

	if (Tex_Return == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
	}

	return Tex_Return;
}

bool Sprite::Draw(SDL_Renderer* ren, SDL_Texture* tex, int xl, int yl, int wl, int hl, int x, int y, int w, int h)
{
		if (ren == nullptr || tex == NULL) {
				return false;
		}

		SDL_Rect srcR;

		srcR.x = xl;
		srcR.y = yl;
		srcR.w = wl;
		srcR.h = hl;
			
		SDL_Rect destR;

		destR.x = x;
		destR.y = y;
		destR.w = w;
		destR.h = h;

		SDL_RenderCopy(ren, tex, &srcR, &destR);
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
