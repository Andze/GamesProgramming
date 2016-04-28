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

bool Sound::PlaySound(Mix_Chunk *SFX, int channel)
{
	if (!Mix_Playing(channel))
	{
		Mix_PlayChannel(channel, SFX, 0);
	}
	return true;
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

bool Sound::PauseMusic(Mix_Music *Music, int Volume)
{
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(Music, -1);
		Mix_VolumeMusic(Volume);
		Mix_Volume(-1, Volume);
	}
	//If music is being played
	else
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			Mix_ResumeMusic();
			Mix_VolumeMusic(Volume);
			Mix_Volume(-1, Volume);
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
			Mix_VolumeMusic(0);
			Mix_Volume(-1, 0);
		}
	}
	return true;
}

bool Sound::SetVolume(int Volume)
{
	Mix_VolumeMusic(Volume);
	Mix_Volume(-1, Volume);
	printf("volume is now : %d\n", Mix_VolumeMusic(-1));
	return true;
}
Sound::Sound()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sounds Loaded");
}


Sound::~Sound()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprite	Destructed(%p)", this);
}
