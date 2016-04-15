#include "Sound.h"

Mix_Chunk* Sound::LoadSound(char* File)
{
	

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

Sound::Sound()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sounds Loaded");
}


Sound::~Sound()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Destructed(%p)", this);
}
