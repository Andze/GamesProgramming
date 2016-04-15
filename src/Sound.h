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

	~Sound();
};

#endif /* end of include guard: */