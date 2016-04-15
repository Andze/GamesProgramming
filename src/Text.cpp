#include "Text.h"

Text::Text(int x, int y, int w, int h)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Text Constructed(%p)", this);
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
}

SDL_Texture* Text::LoadText(char* File, char *text, int size, int R, int G, int B, SDL_Renderer* Render)
{
	TTF_Font* font = TTF_OpenFont(File, size);

	if (font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
	}

	SDL_Color Color = { R, G, B };

	SDL_Surface* Surf_Temp = nullptr;
	SDL_Texture* Tex_Return = nullptr;

	Surf_Temp = TTF_RenderText_Solid(font, text, Color);
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

bool Text::DrawText(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, int w, int h)
{
	if (ren == nullptr || tex == NULL) {
		return false;
	}

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;
	destR.w = w;
	destR.h = h;

	SDL_RenderCopy(ren, tex, NULL, &destR);

	return true;
}

TTF_Font* Text::LoadFont(char* File, int size)
{
	TTF_Font* font = TTF_OpenFont(File, size);
	if (font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

	}

	return font;
}

Text::Text(const Text& Text) : rectangle(Text.rectangle)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Text Constructed(%p) - Copied from(%p)", this, Text);
}

Text::~Text()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sounds Loaded");
}
