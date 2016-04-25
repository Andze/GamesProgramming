
#include "common.h"
#include "Sprite.h"
#include "Text.h"
#include "Sound.h"
#include "Score.h"
#include "Button.h"



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
SDL_Texture *tex1; //pointer to the SDL_Texture

SDL_Event event;

//Text
SDL_Texture *messageTexture[4]; //pointer to the SDL_Texture for message

SDL_Texture *PauseTexture[3]; //pointer to the SDL_Texture for pause menu

SDL_Texture *MenuTexture[10];

//Score
SDL_Texture *ScoreTexture;
//High Score
SDL_Texture *HScoreTexture;
//Font
TTF_Font *font = nullptr;

//Player
SDL_Rect Player;
SDL_Rect Animation;

//Current animation frame 
int frame = 0;

int PlayerScore = 0, HighScore = 0, Temp = 0, Lives = 3, Level = 1;
int ScreenSize_X = 700, ScreenSize_Y = 875;
//flags to be used
bool done = false, loaded = false, Menu = true, Pause = false, Game = false, Fullscreen = false, OpeningSong = false;

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
		if (Pause == true)
		{
			Pause = Button::CreateButton(275, 400, 150, 40, &event);
			Game = Button::CreateButton(300, 500, 100, 40, &event);
			if (Game == false)
			{
				Menu = true;
				Pause = false;
			}
		}

		if (Menu == true)
		{
			Menu = Button::CreateButton(275, 775, 150, 40, &event);
			if (Menu == false)
			{
				Game = true;
				Pause = false;
			}
		}

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
					//hit escape to exit or pause if the game is running
					case SDLK_ESCAPE: 
						if (Game == true)
						{
							if (Pause == false)
							{
								Pause = true;
								SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Pause = true");
							}
							else
							{
								Pause = false;
								SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Pause = false");
							}
						}
						if (Menu == true)
						{
							done = true;
						}
						break;
						

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
						//Mix_PlayChannel(-1, SFX_OpeningSong, 0);
						//Set Fullscreen
						SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
						break;

						//Play medium sound effect
					case SDLK_2:
						//Mix_PlayChannel(-1, SFX_WakaWaka, 0);
						//Set Windowed
						SDL_SetWindowFullscreen(win, 0);
						break;

						//Play low sound effect
					case SDLK_3:
						//Mix_PlayChannel(-1, SFX_Dies, 0);
						//Set original size
						SDL_SetWindowSize(win, ScreenSize_X, ScreenSize_Y);
						break;

						//Play scratch sound effect
					case SDLK_4:
						//Mix_PlayChannel(-1, SFX_EatingGhost, 0);
						//Set Resolution
						SDL_SetWindowSize(win, 1024, 768);
						break;

						//Add score
					case SDLK_5:
						PlayerScore += 10;
						SDL_SetWindowSize(win, 1280, 720);
						break;

					case SDLK_6:
						SDL_SetWindowSize(win, 1600, 900);
						break;
						

					case SDLK_9:
						Level++;
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
	if (Pause == true)
	{
		UP = false;
		DOWN = false;
		LEFT = false;
		RIGHT = false;
	}
	if (UP == true)
	{
		Player.y -= 3;

		Animation.x = 1515;
		Animation.y = 158;
	}
	if (DOWN == true)
	{
		Player.y += 3;
		
		Animation.x = (1515 + 38);
		Animation.y = 158;
	
	}
	if (RIGHT == true)
	{
		Player.x += 3;
		Animation.y = 0;
		Animation.x = (1515 + 38);
	}
	if (LEFT == true)
	{
		Player.x -= 3;
		Animation.y = 0;
		Animation.x = 1515;
	}
	if (OpeningSong == true)
	{	
		Mix_PlayChannel(-1, SFX_OpeningSong, 0);	
		printf("Playing sound");
		OpeningSong = false;	
	}
}

void cleanExit(int returnValue)
{
	Score::SaveHighScore("./assets/Score/Score.txt", PlayerScore, HighScore);

	if (messageTexture != nullptr) SDL_DestroyTexture(messageTexture[0]);
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

unsigned int lastTime = 0, currentTime;

void render()
{
		//Set logical size so the same images are rendered regardless of window size.
		SDL_RenderSetLogicalSize(ren, ScreenSize_X, ScreenSize_Y);
		//First clear the renderer
		SDL_RenderClear(ren);
		
		Uint32 ticks = SDL_GetTicks();
		Uint32 seconds = ticks / 1000;
		//Diffrent timers for Sprites with more or less frames
		Uint32 Pacman = (ticks / 100) % 4;
		Uint32 MenuGhost = (ticks / 200) % 2;


		if (Game == true)
		{
			//Current time
			// Print a report once per second
			currentTime = SDL_GetTicks();
			if (currentTime > lastTime + 1000) {
				printf("Report: %d\n", currentTime);
				lastTime = currentTime;
			}

			////5 Second Delay before the game start
			//if (Menu <  5000)
			//{
			//	//OpeningSong = true;
			//	
			//	UP = false;
			//	DOWN = false;
			//	RIGHT = false;
			//	LEFT = false;

			//	//Draw Ready and player text for a short time
			//	Text::DrawText(ren, messageTexture[3], 225, 330, 250, 50);
			//	Text::DrawText(ren, messageTexture[4], 300, 475, 100, 50);
			//}
			

			

			//Draw the Score and High Score
			// DrawScore   Render,Texture,		X,	Y,	W,	H
			Score::DrawScore(ren, ScoreTexture, 200, 45, 60, 20);
			Score::DrawScore(ren, HScoreTexture, 370, 45, 60, 20);

			//Drawing Text
			// DrawText Function, MessageTex,		 X , Y, W, H,
			Text::DrawText(ren, messageTexture[0], 275, 0, 150, 40);
			Text::DrawText(ren, messageTexture[1], 180, 0, 50, 40);


			//Drawing Sprites
			//			Screen,Img,Source Rectangle, Destination Rectangle
			//Background
			Sprite::Draw(ren, tex, 600, 0, 600, 656, 5, 75, 685, 752);

			//Pacman
			Sprite::Draw(ren, tex, Animation.x, Animation.y + (Pacman * 40), 38,  38, Player.x, Player.y, 42, 42);

			//Level
			if (Level > 0)
			{	
				//Cherry
				Sprite::Draw(ren, tex, 1390, 0, 38, 38, 600, 830, 42, 42);
			}
			if (Level > 1)
			{
				//Cherry
				Sprite::Draw(ren, tex, 1390, 40, 38, 38, 550, 830, 42, 42);
			}
			if (Level > 2)
			{
				//Cherry
				Sprite::Draw(ren, tex, 1390, 80, 38, 38, 500, 830, 42, 42);
			}
			

			//Lives
			if (Lives > 1)
			{
				Sprite::Draw(ren, tex, 1515, 40, 38, 38, 50 ,830, 42, 42);
			}
			if (Lives > 2)
			{
				Sprite::Draw(ren, tex, 1515, 40, 38, 38, 100, 830, 42, 42);
			}
			if (Lives > 3)
			{
				Sprite::Draw(ren, tex, 1515, 40, 38, 38, 150, 830, 42, 42);
			}
			
		}

		if (Pause == true)
		{
			//Draw texture for menu
			Sprite::Draw(ren, tex1, 1218, 280, 138, 205, 225, 250, 250, 350);
			//Draw text for menu
			Text::DrawText(ren, PauseTexture[1], 275, 300, 150, 40);
			//Resume Text
			Text::DrawText(ren, PauseTexture[2], 275, 400, 150, 40);
			//Quit Text
			Text::DrawText(ren, PauseTexture[3], 300, 500, 100, 40);
		}
		

		if (Menu == true)
		{
			//Drawing Characters next to there text
			Sprite::Draw(ren, tex, 1758, MenuGhost * 40, 40, 40, 150, 200, 40, 40);
			Sprite::Draw(ren, tex, 1675, MenuGhost * 40, 40, 40, 150, 300, 40, 40);
			Sprite::Draw(ren, tex, 1717, MenuGhost * 40, 40, 40, 150, 400, 40, 40);
			Sprite::Draw(ren, tex, 1635, MenuGhost * 40, 40, 40, 150, 500, 40, 40);

			//Drawing Dots 
			Sprite::Draw(ren, tex, 26, 47, 12, 12, 283, 658, 12, 12);
			Sprite::Draw(ren, tex, 18, 61, 25, 25, 275, 700, 25, 25);

			//Draw text for menu
			//CHARACTERS / NICKNAME
			Text::DrawText(ren, MenuTexture[1], 200, 100, 300, 40);
			//Characters BLINKY,PINKY,INKY,CLYDE
			Text::DrawText(ren, MenuTexture[2], 200, 200, 300, 40);
			Text::DrawText(ren, MenuTexture[3], 200, 300, 300, 40);
			Text::DrawText(ren, MenuTexture[4], 200, 400, 300, 40);
			Text::DrawText(ren, MenuTexture[5], 200, 500, 300, 40);

			//Point values
			Text::DrawText(ren, MenuTexture[6], 310, 650, 80, 30);
			Text::DrawText(ren, MenuTexture[7], 310, 700, 80, 30);

			//Play button
			Text::DrawText(ren, MenuTexture[8], 275, 775, 150, 40);
			
		}

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
	messageTexture[0] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "HIGH SCORE" , 96,	255,255,255,	ren);
	messageTexture[1] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "1UP", 96, 255, 255, 255, ren);
	messageTexture[3] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "PLAYER ONE", 150, 73, 233, 202, ren);
	messageTexture[4] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "READY!", 150, 245, 255, 0, ren);


	//Text used for the Pause menu using the TEXT class to load message onto texture array
	PauseTexture[1] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "Paused",	150,		255, 255, 255,  ren);
	PauseTexture[2] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "Resume", 125, 255, 255, 255, ren);
	PauseTexture[3] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "Quit", 125, 255, 255, 255, ren);

	MenuTexture[1] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "  CHARACTER / NICKNAME", 150, 255, 255, 255, ren);
	MenuTexture[2] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "- SHADOW      'BLINKY'", 150, 255, 0, 0, ren);
	MenuTexture[3] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "- SPEEDY      'PINKY'", 150, 252, 190, 227, ren);
	MenuTexture[4] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "- BASHFUL     'INKY'", 150, 73, 233, 202, ren);
	MenuTexture[5] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "- POKEY       'CLYDE'", 150, 255, 191, 81, ren);
	MenuTexture[6] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "10 PTS", 150, 255, 255, 255, ren);
	MenuTexture[7] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "50 PTS", 150, 255, 255, 255, ren);
	MenuTexture[8] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "PLAY", 150, 255, 255, 255, ren);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Text Loaded");
}


void LoadSprites()
{	
	//Set Players intial position
	Player.x = 325;	Player.y = 625;

	//Set Players intial position
	Animation.x = 1515;	Animation.y = 0;

	//Add Sprites to SpriteList
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Adding sprites...");
	
	//Loads sprite sheet into texture
	tex = Sprite::OnLoad("./assets/Imgs/Pacman_SpriteSheet.png", ren, 0, 0, 0);
	tex1 = Sprite::OnLoad("./assets/Imgs/Pacman_SpriteSheet.png", ren, 255, 0, 0);

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sprites added");

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
	win = SDL_CreateWindow("Pacman", 300, 100, ScreenSize_X, ScreenSize_Y, SDL_WINDOW_SHOWN);

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

////Draw Sprites in sprite list
//for (auto const& spriteKv : spriteList) //unique_ptr can't be copied, so use reference
//{
//	//sprite &thisSprite = spriteKv.second
//	//std::cout << spriteKv.second->Lrectangle.x << std::endl;;
//	//SDL_RenderCopy(ren, tex, &spriteKv.second->Lrectangle, &spriteKv.second->rectangle);
//	//SDL_RenderCopy(ren, tex, &currentClip, &spriteKv.second->rectangle);
//	//spriteList["Pacman_Whole"]->rectangle.x

//}
////spriteList["Pacman_Whole"]->rectangle