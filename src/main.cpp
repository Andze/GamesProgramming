
#include "common.h"
#include "Sprite.h"
#include "Text.h"


#ifdef _WIN32 // compiling on windows
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#else // NOT compiling on windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

using namespace std;

std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_Renderer *ren; //pointer to the SDL_Renderer
SDL_Surface *surface; //pointer to the SDL_Surface
SDL_Texture *tex; //pointer to the SDL_Texture
SDL_Surface *messageSurface; //pointer to the SDL_Surface for message
SDL_Texture *messageTexture; //pointer to the SDL_Texture for message
SDL_Rect message_rect; //SDL_rect for the message

SDL_Surface *HighScore; //pointer to the SDL_Surface for message
SDL_Surface *Score; //pointer to the SDL_Surface for message
SDL_Rect HighScore_rect; //SDL_rect for the message
SDL_Rect Score_rect; //SDL_rect for the message
SDL_Texture *messageTexture1; //pointer to the SDL_Texture for message
SDL_Texture *messageTexture2; //pointer to the SDL_Texture for message

bool done = false;

//std::vector<unique_ptr<Sprite>> spriteList;
std::map<string, unique_ptr<Sprite>> spriteList;

std::map<string, unique_ptr<Text>> textList;

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *SFX_OpeningSong = NULL;
Mix_Chunk *SFX_WakaWaka = NULL;
Mix_Chunk *SFX_Dies = NULL;
Mix_Chunk *SFX_Cherry = NULL;
Mix_Chunk *SFX_EatingGhost = NULL;
Mix_Chunk *SFX_ExtraLife = NULL;

void handleInput()
{
	//Event-based input handling
	//The underlying OS is event-based, so **each** key-up or key-down (for example)
	//generates an event.
	//  - https://wiki.libsdl.org/SDL_PollEvent
	//In some scenarios we want to catch **ALL** the events, not just to present state
	//  - for instance, if taking keyboard input the user might key-down two keys during a frame
	//    - we want to catch based, and know the order
	//  - or the user might key-down and key-up the same within a frame, and we still want something to happen (e.g. jump)
	//  - the alternative is to Poll the current state with SDL_GetKeyboardState

	SDL_Event event; //somewhere to store an event

	//NOTE: there may be multiple events per frame
	while (SDL_PollEvent(&event)) //loop until SDL_PollEvent returns 0 (meaning no more events)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			done = true; //set donecreate remote branch flag if SDL wants to quit (i.e. if the OS has triggered a close event,
							//  - such as window close, or SIGINT
			break;

			//keydown handling - we should to the opposite on key-up for direction controls (generally)
		case SDL_KEYDOWN:
			//Keydown can fire repeatable if key-repeat is on.
			//  - the repeat flag is set on the keyboard event, if this is a repeat event
			//  - in our case, we're going to ignore repeat events
			//  - https://wiki.libsdl.org/SDL_KeyboardEvent
			if (!event.key.repeat)
				switch (event.key.keysym.sym)
				{
					//hit escape to exit
					case SDLK_ESCAPE: done = true;

						//Play high sound effect
					case SDLK_1:
						Mix_PlayChannel(-1, SFX_OpeningSong, 0);
						break;

						//Play medium sound effect
					case SDLK_2:
						Mix_PlayChannel(-1, SFX_WakaWaka, 0);
						break;

						//Play low sound effect
					case SDLK_3:
						Mix_PlayChannel(-1, SFX_Dies, 0);
						break;

						//Play scratch sound effect
					case SDLK_4:
						Mix_PlayChannel(-1, SFX_EatingGhost, 0);
						break;

					case SDLK_9:
						//If there is no music playing
						if (Mix_PlayingMusic() == 0)
						{
							//Play the music
							Mix_PlayMusic(gMusic, -1);
						}
						//If music is being played
						else
						{
							//If the music is paused
							if (Mix_PausedMusic() == 1)
							{
								//Resume the music
								Mix_ResumeMusic();
							}
							//If the music is playing
							else
							{
								//Pause the music
								Mix_PauseMusic();
							}
						}
				}
			break;
		}
	}
}
// end::handleInput[]

// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
  //CHANGE ME
}

void render()
{
		//First clear the renderer
		SDL_RenderClear(ren);

		//Draw the texture
		SDL_RenderCopy(ren, tex, NULL, NULL);

		//Draw Sprites in sprite list
		for (auto const& spriteKv : spriteList) //unique_ptr can't be copied, so use reference
		{
			//sprite &thisSprite = spriteKv.second
			SDL_RenderCopy(ren, tex, NULL, &spriteKv.second->rectangle);
		}

		//Draw Text in Text list
		for (auto const& textKv : textList) //unique_ptr can't be copied, so use reference
		{
			//sprite &thisSprite = spriteKv.second
			SDL_RenderCopy(ren, tex, NULL, &textKv.second->rectangle);
		}


		//Draw the text
		SDL_RenderCopy(ren, messageTexture, NULL, &message_rect);
		SDL_RenderCopy(ren, messageTexture1, NULL, &HighScore_rect);

		//Update the screen
		SDL_RenderPresent(ren);
}

void cleanExit(int returnValue)
{
	if (messageTexture != nullptr) SDL_DestroyTexture(messageTexture);
	if (messageTexture1 != nullptr) SDL_DestroyTexture(messageTexture1);
	if (messageTexture2 != nullptr) SDL_DestroyTexture(messageTexture2);
	if (tex != nullptr) SDL_DestroyTexture(tex);
	if (ren != nullptr) SDL_DestroyRenderer(ren);
	if (win != nullptr) SDL_DestroyWindow(win);

	//Free the sound effects
	Mix_FreeChunk(SFX_OpeningSong);
	Mix_FreeChunk(SFX_WakaWaka);
	Mix_FreeChunk(SFX_Dies);
	Mix_FreeChunk(SFX_Cherry);
	Mix_FreeChunk(SFX_EatingGhost);
	Mix_FreeChunk(SFX_ExtraLife);

	//Set the variables back to empty
	SFX_OpeningSong = NULL;
	SFX_WakaWaka = NULL;
	SFX_Dies = NULL;
	SFX_Cherry = NULL;
	SFX_EatingGhost = NULL;
	SFX_ExtraLife = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	SDL_Quit();
	exit(returnValue);
}

void LoadText()
{
	//Load Font
	if (TTF_Init() == -1)
	{
		std::cout << "TTF_Init Failed: " << TTF_GetError() << std::endl;
		cleanExit(1);
	}

	TTF_Font* sans = TTF_OpenFont("./assets/Fonts/Hack-Regular.ttf", 96);
	if (sans == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		cleanExit(1);
	}

	//display text
	SDL_Color White = { 255, 255, 255 };
	messageSurface = TTF_RenderText_Solid(sans, "High Score", White);
	messageTexture = SDL_CreateTextureFromSurface(ren, messageSurface);
	message_rect.x = 325;
	message_rect.y = 0;
	message_rect.w = 150;
	message_rect.h = 40;

	HighScore = TTF_RenderText_Solid(sans, "000", White);
	messageTexture1 = SDL_CreateTextureFromSurface(ren, HighScore);
	HighScore_rect.x = 370;
	HighScore_rect.y = 45;
	HighScore_rect.w = 60;
	HighScore_rect.h = 20;
}

void LoadSprites()
{
	//Add Sprites to SpriteList
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Adding sprites...");
	//Adding Sprites to list with uniquie pointer and X,Y,W,H
	//spriteList.insert(std::unique_ptr<Sprite>(new Sprite(0, 0, 200, 86)));
	//spriteList.insert(std::unique_ptr<Sprite>(new Sprite(200, 200, 200, 86)));
	spriteList.emplace("Sprite1", std::unique_ptr<Sprite>(new Sprite(0, 0, 200, 86)));
	spriteList.emplace("Sprite2", std::unique_ptr<Sprite>(new Sprite(200, 200, 200, 86)));

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprites added");

	//Add Text to textList
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Adding Text...");

	//Adding Sprites to list with uniquie pointer and X,Y,W,H
	textList.emplace("Text1", std::unique_ptr<Text>(new Text("Test", 0, 0, 200, 86)));
	textList.emplace("Text2", std::unique_ptr<Text>(new Text("Test", 200, 200, 200, 86)));

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Text added");
}

void LoadSound()
{
	//Initialize SDL_mixer http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
	//Sound Frequency, Sample format, Hardware channels
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
		cleanExit(1);
	}

	//Load music 
	std::string MusicPath = "./assets/Sound/Pacman Siren Clean Loop.mp3";
	gMusic = Mix_LoadMUS(MusicPath.c_str());
	if (gMusic == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		cleanExit(1);
	}

	//Load sound effects
	std::string OpeningSong = "./assets/Sound/Pacman Opening Song.mp3";
	SFX_OpeningSong = Mix_LoadWAV(OpeningSong.c_str());
	if (SFX_OpeningSong == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		cleanExit(1);
	}
	//Load sound effects
	std::string WakaWaka = "./assets/Sound/PacmanWakaWaka1.Wav";
	SFX_WakaWaka = Mix_LoadWAV(WakaWaka.c_str());
	if (SFX_WakaWaka == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		cleanExit(1);
	}

	//Load sound effects
	std::string EatingGhost = "./assets/Sound/Pacman Eating Ghost.Wav";
	SFX_EatingGhost = Mix_LoadWAV(EatingGhost.c_str());
	if (SFX_EatingGhost == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		cleanExit(1);
	}

	//Load sound effects
	std::string Dies = "./assets/Sound/Pacman Dies.Wav";
	SFX_Dies = Mix_LoadWAV(Dies.c_str());
	if (SFX_Dies == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		cleanExit(1);
	}
	
}

// based on http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
int main( int argc, char* args[] )
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL initialised OK!\n";

	//create window
	win = SDL_CreateWindow("Pacman", 100, 100, 800, 800, SDL_WINDOW_SHOWN);

	//error handling
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL CreatedWindow OK!\n";
	

	//turning V Sync On 
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Turning V Sync off
	//ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED );
	
	

	if (ren == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	//Load Img
	std::string imagePath = "./assets/Imgs/Opengl-logo.svg.png";
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr){
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (tex == nullptr){
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	


	//			Timer
	//auto t1 = Clock::now();
	//auto t2 = Clock::now();
	/*std::cout << "Delta t2-t1: "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
		<< " nanoseconds" << std::endl;*/

	LoadSprites();

	LoadText();

	LoadSound();

	while (!done) //loop until done flag is set)

	{	
		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		SDL_Delay(20); // unless vsync is on??
	}

	cleanExit(0);
	return 0;
}
