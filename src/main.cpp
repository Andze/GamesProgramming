
#include "common.h"
#include "Sprite.h"
#include "Text.h"
#include "Sound.h"
#include "Score.h"


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

//Window Name
std::string Pacman;
//Window
SDL_Window *win; //pointer to the SDL_Window
//Render
SDL_Renderer *ren; //pointer to the SDL_Renderer
//Image Texture
SDL_Texture *tex; //pointer to the SDL_Texture

//Text
SDL_Texture *messageTexture; //pointer to the SDL_Texture for message

//Score
SDL_Texture *ScoreTexture;
//High Score
SDL_Texture *HScoreTexture;
//Font
TTF_Font *font = nullptr;

//Player
SDL_Rect Player;
SDL_Rect Animation;

int PlayerScore = 0, HighScore = 0, Temp = 0;
int ScreenSize_X = 700, ScreenSize_Y = 875;
bool done = false , loaded = false;
int *CurrentSprite = nullptr;

//std::vector<unique_ptr<Sprite>> spriteList;
std::map<string, unique_ptr<Sprite>> spriteList;

//-> class AnimatedSprite or SpriteAnimation

// orangeGhost , which spritelist is active right now -> class renderableThing, has a list of SpriteAnimation, and which is active


//The music that will be played
Mix_Music *gMusic = nullptr;

//The sound effects that will be used
Mix_Chunk *SFX_OpeningSong = nullptr;
Mix_Chunk *SFX_WakaWaka = nullptr;
Mix_Chunk *SFX_Dies = nullptr;
Mix_Chunk *SFX_Cherry = nullptr;
Mix_Chunk *SFX_EatingGhost = nullptr;
Mix_Chunk *SFX_ExtraLife = nullptr;

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
						DOWN = false;
						RIGHT = false;
						LEFT = false;
						break;
					case SDLK_DOWN:
						DOWN = true;
						RIGHT = false;
						LEFT = false;
						UP = false;
						break;
					case SDLK_RIGHT:
						RIGHT = true;
						LEFT = false;
						UP = false;
						DOWN = false;
						break;
					case SDLK_LEFT:
						//True
						LEFT = true;
						//False
						UP = false;
						DOWN = false;
						RIGHT = false;
						break;

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

						//Add score
					case SDLK_5:
						PlayerScore += 10;
						ScreenSize_X += 10;
						SDL_SetWindowSize(win, 1080, 720);
						break;

					case SDLK_6:
						SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
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
		Player.y -= 3;
	}
	if (DOWN == true)
	{
		Player.y += 3;
		Animation.y += 1;
		if (Animation.y > 152)
		{
			Animation.y = 0;
		}
	}
	if (RIGHT == true)
	{
		Player.x += 3;
		Animation.x = (1515 + 38);
	}
	if (LEFT == true)
	{
		Player.x -= 3;
		Animation.x = 1515;
	}
}

void cleanExit(int returnValue)
{
	Score::SaveHighScore("./assets/Score/Score.txt", PlayerScore, HighScore);

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

void render()
{
		SDL_RenderSetLogicalSize(ren, ScreenSize_X, ScreenSize_Y);
		//First clear the renderer
		SDL_RenderClear(ren);

		//SDL_SetWindowSize(win, 1080, 720);
		//Draw the Score and High Score
		// DrawScore   Render,Texture,		X,	Y,	W,	H
		Score::DrawScore(ren, ScoreTexture, 200, 45, 60, 20);
		Score::DrawScore(ren, HScoreTexture, 370, 45, 60, 20);
		
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
		Sprite::Draw(ren, tex, 600, 0, 600, 656, 5, 75, 685, 752);
		//Pacman
		Sprite::Draw(ren, tex, Animation.x, Animation.y , 38, 38, Player.x, Player.y, 42, 42);
		
		//Drawing Text
		// DrawText Function, MessageTex, X , Y, W, H,
		Text::DrawText(ren, messageTexture, 275, 0, 150, 40);

		//Update the screen
		SDL_RenderPresent(ren);
		
}



void Score()
{
	if (loaded == false)
	{
		//Load hacktype face
		font = Score::LoadFont("./assets/Fonts/Hack-Regular.ttf", 96);

		//Load in Highscore from txt file
		HighScore = Score::LoadHighscore("./assets/Score/Score.txt", HighScore);

		loaded = true;

		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "FONT LOADED");
	}
	if (loaded == true)
	{	
		if (ScoreTexture != nullptr) SDL_DestroyTexture(ScoreTexture);
		if (HScoreTexture != nullptr) SDL_DestroyTexture(HScoreTexture);

		//LoadScore into Tex(font,Score,Color(RGB),Render)
		ScoreTexture = Score::LoadScore(font,PlayerScore,255,255,255,ren);
		//LoadScore into Tex(font,Score,Color(RGB),Render)
		HScoreTexture = Score::LoadScore(font, HighScore, 255, 255, 255, ren);
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
	//Set Players intial position
	Player.x = 60;	Player.y = 90;

	//Set Players intial position
	Animation.x = 1515;	Animation.y = 0;

	//Add Sprites to SpriteList
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Adding sprites...");
	
	//Loads sprite sheet into texture
	tex = Sprite::OnLoad("./assets/Imgs/Pacman_SpriteSheet.png",ren);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprites added");
	
	//Adding Sprites to list with uniquie pointer and		  Sprite X, Y, W, H	Location X, Y, W, H
	/*spriteList.emplace("Background", std::unique_ptr<Sprite>(new Sprite(226, 0, 226, 248, 5, 75, 685, 752)));
	spriteList.emplace("Pacman_Whole", std::unique_ptr<Sprite>(new Sprite(455,0,15,15,		60,90,42.5,42.5)));
	spriteList.emplace("Pacman_Right_1", std::unique_ptr<Sprite>(new Sprite(472,0,15,15,	80,90,42.5,42.5)));
	spriteList.emplace("Pacman_Right_2", std::unique_ptr<Sprite>(new Sprite(488,0,15,15,	120,90,42.5,42.5)));*/	
}

void LoadSound()
{
	//Add Sprites to SpriteList
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading Sounds...");

	//Load music 
	gMusic = Sound::LoadMusic("./assets/Sound/Pacman Siren Clean Loop.mp3");

	//Load sound effects
	SFX_WakaWaka = Sound::LoadSFX("./assets/Sound/PacmanWakaWaka1.Wav");

	SFX_EatingGhost = Sound::LoadSFX("./assets/Sound/Pacman Eating Ghost.Wav");

	SFX_Dies = Sound::LoadSFX("./assets/Sound/Pacman Dies.Wav");

	SFX_OpeningSong = Sound::LoadSFX("./assets/Sound/Pacman Opening Song.mp3");

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sounds added");
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
	win = SDL_CreateWindow("Pacman", 100, 100, ScreenSize_X, ScreenSize_Y, SDL_WINDOW_SHOWN);

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
	if (ren == nullptr)	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	//Turning V Sync off
	//ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED );

	
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

