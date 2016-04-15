
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

std::string Pacman;
SDL_Window *win; //pointer to the SDL_Window

SDL_Renderer *ren; //pointer to the SDL_Renderer
SDL_Surface *surface; //pointer to the SDL_Surface
SDL_Texture *tex; //pointer to the SDL_Texture

SDL_Surface *messageSurface; //pointer to the SDL_Surface for message
SDL_Texture *messageTexture; //pointer to the SDL_Texture for message
SDL_Rect message_rect; //SDL_rect for the message

//Score
SDL_Rect Score_rect; //SDL_rect for the Score
SDL_Surface *ScoreSurface;
SDL_Texture *ScoreTexture;
//High Score
SDL_Rect HScore_rect; //SDL_rect for the Score
SDL_Surface *HScoreSurface = nullptr;
SDL_Texture *HScoreTexture;

//Sprite
const int Right = 3;
SDL_Rect Sprite_rect[ Right ];
Uint32 sprite;

SDL_Color White = { 255, 255, 255 };
TTF_Font *font = nullptr;

int PlayerScore = 0;
int HighScore = 0;
int Temp = 0;
bool done = false;
bool loaded = false;
int *CurrentSprite = NULL;



//std::vector<unique_ptr<Sprite>> spriteList;
std::map<string, unique_ptr<Sprite>> spriteList;

//-> class AnimatedSprite or SpriteAnimation

// orangeGhost , which spritelist is active right now -> class renderableThing, has a list of SpriteAnimation, and which is active


//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *SFX_OpeningSong = NULL;
Mix_Chunk *SFX_WakaWaka = NULL;
Mix_Chunk *SFX_Dies = NULL;
Mix_Chunk *SFX_Cherry = NULL;
Mix_Chunk *SFX_EatingGhost = NULL;
Mix_Chunk *SFX_ExtraLife = NULL;

bool W, A, S, D, UP, DOWN, LEFT, RIGHT = false;

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

					case SDLK_UP:
						UP = true;
						break;
					case SDLK_DOWN:
						DOWN = true;
						break;
					case SDLK_RIGHT:
						RIGHT = true;
						break;
					case SDLK_LEFT:
						LEFT = true;
						break;

					case SDLK_1:
						Mix_PlayChannel(-1, SFX_OpeningSong, 0);
						HighScore += 10;
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
	if (UP == true)
	{
		
	}
	if (DOWN == true)
	{

	}
	if (RIGHT == true)
	{

	}
	if (LEFT == true)
	{
		
	}
}

void render()
{
		Uint32 ticks = SDL_GetTicks();
		Uint32 sprite = (ticks / 1000) % 3;

		//First clear the renderer
		SDL_RenderClear(ren);

		//Draw the texture
		//SDL_RenderCopy(ren, tex, NULL, NULL);

		//Draw the text
		//SDL_RenderCopy(ren, messageTexture, NULL, &message_rect);

		//Draw the Score and High Score
		SDL_RenderCopy(ren, ScoreTexture, NULL, &Score_rect);
		SDL_RenderCopy(ren, HScoreTexture, NULL, &HScore_rect);
		
		//Draw Sprites in sprite list
		for (auto const& spriteKv : spriteList) //unique_ptr can't be copied, so use reference
		{
			//sprite &thisSprite = spriteKv.second
			//std::cout << spriteKv.second->Lrectangle.x << std::endl;;
			//SDL_RenderCopy(ren, tex, &spriteKv.second->Lrectangle, &spriteKv.second->rectangle);
			//SDL_RenderCopy(ren, tex, &currentClip, &spriteKv.second->rectangle);
			//spriteList["Pacman_Whole"]->rectangle.x
		
		}
		//spriteList["Pacman_Whole"]->rectangle

		//Drawing Sprites
		//			Screen,Img,Source Rectangle, Destination Rectangle
		//Background
		Sprite::Draw(ren, tex, 226, 0, 226, 248, 5, 75, 685, 752);
		//Pacman
		Sprite::Draw(ren, tex, 455, 0, 15, 15, 60, 90, 42.5, 42.5);
		
		//Drawing Text
		// DrawText Function, MessageTex, X , Y, W, H,
		Text::DrawText(ren, messageTexture, 275, 0, 150, 40);

		//Update the screen
		SDL_RenderPresent(ren);
		
}

void cleanExit(int returnValue)
{
	if (messageTexture != nullptr) SDL_DestroyTexture(messageTexture);
	if (tex != nullptr) SDL_DestroyTexture(tex);
	if (ren != nullptr) SDL_DestroyRenderer(ren);
	if (win != nullptr) SDL_DestroyWindow(win);

	//Quit SDL_ttf
	TTF_Quit();

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

void Score()
{
	if (loaded == false)
	{
		//Load hacktype face
		font = TTF_OpenFont("./assets/Fonts/Hack-Regular.ttf", 96);
		if (font == nullptr)
		{
			std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
			cleanExit(1);
			
		}
		loaded = true;
		std::cout << "FONT LOADED " << std::endl;
	}
	if (loaded == true)
	{	
		//Score variables being pasted into string stream
		stringstream Pscore, Hscore;
		Pscore << PlayerScore;
		Hscore << HighScore;

		if (ScoreSurface != nullptr) SDL_FreeSurface(ScoreSurface);
		if (ScoreTexture != nullptr) SDL_DestroyTexture(ScoreTexture);

		//Setting Score Int to Score Texture to be used by render to draw
		ScoreSurface = TTF_RenderText_Solid(font, Pscore.str().c_str(), White);
		ScoreTexture = SDL_CreateTextureFromSurface(ren, ScoreSurface);
		//Rect for where the Score is to be drawn
		Score_rect.x = 200;	
		Score_rect.y = 45;	
		Score_rect.w = 60;	
		Score_rect.h = 20;
		
		if (HScoreSurface != nullptr) SDL_FreeSurface(HScoreSurface);
		if (HScoreTexture != nullptr) SDL_DestroyTexture(HScoreTexture);

		//Setting Score Int to Score Texture to be used by render to draw
		// delete old surface and delete of texture (if they are not nullptr)
		HScoreSurface = TTF_RenderText_Solid(font, Hscore.str().c_str(), White);
		HScoreTexture = SDL_CreateTextureFromSurface(ren, HScoreSurface);
		//Rect for where the Score is to be drawn
		HScore_rect.x = 370;	
		HScore_rect.y = 45;	
		HScore_rect.w = 60;
		HScore_rect.h = 20;
	}
}		


void LoadText()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Adding Text...");

	//Using Text class to load a message to a texture to be drawn
	//Texture to store message			Font to be used,				Text,		Size,   ColourRGB,	   Render
	messageTexture = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "HIGH SCORE" , 96,	255,255,255,	ren);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Text Loaded");
}


void LoadSprites()
{
	tex = Sprite::OnLoad("./assets/Imgs/Pac-Man.png",ren);
	
	//Add Sprites to SpriteList
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Adding sprites...");
	//Adding Sprites to list with uniquie pointer and		  Sprite X, Y, W, H	Location X, Y, W, H
	spriteList.emplace("Background", std::unique_ptr<Sprite>(new Sprite(226, 0, 226, 248, 5, 75, 685, 752)));
	spriteList.emplace("Pacman_Whole", std::unique_ptr<Sprite>(new Sprite(455,0,15,15,		60,90,42.5,42.5)));
	spriteList.emplace("Pacman_Right_1", std::unique_ptr<Sprite>(new Sprite(472,0,15,15,	80,90,42.5,42.5)));
	spriteList.emplace("Pacman_Right_2", std::unique_ptr<Sprite>(new Sprite(488,0,15,15,	120,90,42.5,42.5)));
	

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprites added");
}

void LoadSound()
{
	//Load music 
	gMusic = Sound::LoadSound("./assets/Sound/Pacman Siren Clean Loop.mp3");

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
void init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL initialised OK!\n";

	//Initialize SDL_mixer http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
	//Sound Frequency, Sample format, Hardware channels
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
		cleanExit(1);
	}

	//create window
	win = SDL_CreateWindow("Pacman", 100, 100, 700, 875, SDL_WINDOW_SHOWN);

	//error handling
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL CreatedWindow OK!\n";

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		cleanExit(1);
	}

	//turning V Sync On 
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Turning V Sync off
	//ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED );

	if (ren == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
}
// based on http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
int main( int argc, char* args[] )
{
	init();

	LoadSprites();

	LoadText();

	LoadSound();

	while (!done) //loop until done flag is set)

	{	
		Score();

		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		SDL_Delay(20); // unless vsync is on??
	}

	cleanExit(0);
	return 0;
}
