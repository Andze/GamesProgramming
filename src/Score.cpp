#include "Score.h"

Score::Score()
{
}

TTF_Font* Score::LoadFont(char* File, int size)
{
	TTF_Font* font = TTF_OpenFont(File, size);
	if (font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

	}

	return font;
}


SDL_Texture* Score::loadScore(TTF_Font* Font, int Score, int R, int G, int B, SDL_Renderer* Render);
{
	/*TTF_Font* font = TTF_OpenFont(File, size);

	if (font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
	}*/

	SDL_Color Color = { R, G, B };

	SDL_Surface* Surf_Temp = nullptr;
	SDL_Texture* Tex_Return = nullptr;

	Surf_Temp = TTF_RenderText_Solid(&Font, Score, Color);
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



Score::~Score()
{
}
