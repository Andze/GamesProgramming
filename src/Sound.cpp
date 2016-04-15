#include "Sound.h"

Mix_Chunk* Sound::LoadSFX(char* File)
{
	Mix_Chunk *SFX = nullptr;

	SFX = Mix_LoadWAV(File);
	if (SFX == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	return SFX;
}

Mix_Music* Sound::LoadMusic (char* File)
{
	Mix_Music *Music = nullptr;

	Music = Mix_LoadMUS(File);
	if (Music == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	return Music;
}
Sound::Sound()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sounds Loaded");
}


Sound::~Sound()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Destructed(%p)", this);
}
