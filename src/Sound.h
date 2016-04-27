#pragma once
#ifndef Sound_h
#define Sound_h

#include "common.h"


class Sound
{
public:
	Sound();

	static Mix_Chunk* LoadSFX(char* File);

	static Mix_Music* Sound::LoadMusic(char* File);

	static bool PlaySound(Mix_Chunk *SFX, int channel);

	~Sound();
};

#endif /* end of include guard: */