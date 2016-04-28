
#include "common.h"

#ifdef _WIN32 // compiling on windows
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#else // NOT compiling on windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "main.h"
#endif

using namespace std;

//Window Name
std::string Pacman;
//Window
SDL_Window *win; //pointer to the SDL_Window
SDL_Window *win2; //pointer to the SDL_Window
//Render
SDL_Renderer *ren; //pointer to the SDL_Renderer
SDL_Renderer *ren2; //pointer to the SDL_Renderer
//Image Texture
SDL_Texture *tex; //pointer to the SDL_Texture
SDL_Texture *tex1; //pointer to the SDL_Texture

SDL_Event event;

//Text
SDL_Texture *messageTexture[5]; //pointer to the SDL_Texture for message

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
SDL_Rect Player2;

SDL_Rect GhostMove[3];

SDL_Rect Animation;
SDL_Rect GhostAnimation[3];

//31 x 28
int const Map_Rows = 31 , Map_Collums = 28;

// enum class
enum class PacmanGridStates { EMPTY = 2, WALL = 0, PELLET = 1, BIG_PELLET = 3, GATE = 4, EATEN = 5, EATEN_BIG = 6, Teleport_1, Teleport_2};

PacmanGridStates Map[Map_Rows][Map_Collums] = {
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::BIG_PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::BIG_PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL } ,
	//Centre Teleporter Line 
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::GATE, PacmanGridStates::GATE, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL },
	{ PacmanGridStates::Teleport_1, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::PELLET, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::PELLET, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::Teleport_2 },
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::EMPTY, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::BIG_PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::EMPTY, PacmanGridStates::EMPTY, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::BIG_PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::WALL,PacmanGridStates::WALL,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::WALL,PacmanGridStates::WALL,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::WALL,PacmanGridStates::WALL,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::PELLET,PacmanGridStates::WALL },
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::PELLET, PacmanGridStates::WALL } ,
	{ PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL, PacmanGridStates::WALL }
};

//Current animation frame 
int frame = 0;

int PlayerScore = 0, HighScore = 0, Temp = 0, Lives = 3, Level = 1, Pellets = 244, Volume = 128, GhostsEaten = 0;

int const Start_X = 325, Start_Y = 620;
int const Start_X2 = 325, Start_Y2 = 187;

const int RedGhost_x = 1758;
const int OrangeGhost_x = 1635;
const int PinkGhost_x = 1675;
const int CyanGhost_x = 1717;

const int PlayerSpeed = 3;
const int pixelPerGridCell = 24;
const int pixelOffsetX = 16;
const int pixelOffsetY = 80;
const int WallOffset = 10;
const int BIG_PELLET_Offset = 8;
const int GridCentre = 25;

int ScreenSize_X = 700, ScreenSize_Y = 875, GameTimer = 0;

//flags to be used
bool done = false, loaded = false, Menu = true, Pause = false, Game = false, Fullscreen = false, OpeningSong = false, Levelwin = false, Reset = false, Music = false, BigPellet = false, Dead = false;
bool tmp = true, Died = false, ScoreMSG = false;
bool PlayerColide = false;
//The music that will be played
Mix_Music *gMusic = nullptr;

//The sound effects that will be used
Mix_Chunk *SFX_OpeningSong = nullptr;
Mix_Chunk *SFX_WakaWaka = nullptr;
Mix_Chunk *SFX_Dies = nullptr;
Mix_Chunk *SFX_Cherry = nullptr;
Mix_Chunk *SFX_EatingGhost = nullptr;
Mix_Chunk *SFX_ExtraLife = nullptr;
Mix_Chunk *SFX_BigPellet = nullptr;

bool W, A, S, D, UP, DOWN, LEFT, RIGHT, Ghost_UP,Ghost_DOWN,Ghost_LEFT,Ghost_RIGHT = false;

//callback function 
Uint32 callback( Uint32 interval, void* param);
void Death();
void SetPositions();
void cleanExit(int returnValue);

Uint32 callback(Uint32 interval, void* param)
{ 
	if ((char*)param == "BigPellet")
	{
		BigPellet = false;
	}
	if ((char*)param == "EATPlayer2")
	{
		Player2.x = Start_X2;	Player2.y = Start_Y2; GhostAnimation[0].x = RedGhost_x; GhostAnimation[0].y = 0;
		ScoreMSG = false;
	}
	if ((char*)param == "Dead")
	{
		Dead = false;
		Death();
		if (Lives <= 0)
		{
			Game = false;
			Menu = true;
			Sound::SetVolume(Volume = 0);
		}
	}
	
	//Print callback message 
	//printf( "Callback called back with message: %s\n", (char*)param );
	return 0; 
}
void SetPositions()
{
	Player.x = Start_X;	Player.y = Start_Y;

	GhostMove[0].x = 290; GhostMove[0].y = 400; GhostMove[0].w = 40; GhostMove[0].h = 40;
	GhostMove[1].x = 330; GhostMove[1].y = 400; GhostMove[1].w = 40; GhostMove[1].h = 40;
	GhostMove[2].x = 370; GhostMove[2].y = 400; GhostMove[2].w = 40; GhostMove[2].h = 40;

	GhostAnimation[0].x = RedGhost_x;
	GhostAnimation[1].x = PinkGhost_x;
	GhostAnimation[2].x = CyanGhost_x;
	GhostAnimation[3].x = OrangeGhost_x;

	Player2.x = Start_X2;	Player2.y = Start_Y2;
}
void Death()
{
	tmp = true;
	//Reset Players postion
	SetPositions();
}
void StartGame()
{
	//Reset Score
	PlayerScore = 0;
	//Reset Level
	Level = 1; 
	Lives = 3;
	tmp = true;
	
	Sound::SetVolume(Volume = 128);

	SetPositions();
}

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
				//Initialise variables such as score, level and player pos
				StartGame();
				//Load Menus
				Menu = true;
				Pause = false;
			}
		}

		if (Menu == true)
		{
			Menu = Button::CreateButton(275, 775, 150, 40, &event);
			if (Menu == false)
			{
				//Every time play button is pressed Reset the level map pellets
				Reset = true;
				StartGame();
				//Set game flag for render and simulation
				Game = true;

				//Play the music for game
				Mix_PlayMusic(gMusic, -1);
				
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
								Sound::PauseMusic(gMusic, Volume);
								SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Pause = true");
							}
							else
							{
								Pause = false;
								Sound::PauseMusic(gMusic, Volume);
								SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Pause = false");
							}
						}
						if (Menu == true)	{done = true;}
						break;

					case SDLK_SPACE:
						if (Menu == true)
						{
							Menu = false;
							if (Menu == false)
							{
								Game = true;
								Pause = false;
							}
						}
						break;

					case SDLK_UP:
						UP = true;
						DOWN = false; RIGHT = false; LEFT = false;
						break;

					case SDLK_DOWN:
						DOWN = true;
						RIGHT = false; LEFT = false; UP = false;
						break;

					case SDLK_RIGHT:
						RIGHT = true;
						LEFT = false; UP = false; DOWN = false;
						break;

					case SDLK_LEFT:
						LEFT = true;
						UP = false;	DOWN = false; RIGHT = false;
						break;

					case SDLK_w:
						Ghost_UP = true;
						Ghost_DOWN = false; Ghost_RIGHT = false; Ghost_LEFT = false;
						break;

					case SDLK_s:
						Ghost_DOWN = true;
						Ghost_RIGHT = false; Ghost_LEFT = false; Ghost_UP = false;
						break;

					case SDLK_d:
						Ghost_RIGHT = true;
						Ghost_LEFT = false; Ghost_UP = false; Ghost_DOWN = false;
						break;

					case SDLK_a:
						Ghost_LEFT = true;
						Ghost_UP = false;	Ghost_DOWN = false; Ghost_RIGHT = false;
						break;

					case SDLK_1:
						//Set Fullscreen
						SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
						break;

						//Play medium sound effect
					case SDLK_2:
						//Mix_PlayChannel(-1, SFX_WakaWaka, 0);
						//Set Windowed
						SDL_SetWindowFullscreen(win, 0);
						break;

					case SDLK_3:
						//Mix_PlayChannel(-1, SFX_Dies, 0);
						//Set original size
						SDL_SetWindowSize(win, ScreenSize_X, ScreenSize_Y);
						break;
					case SDLK_4:
			
						//Set Resolution
						SDL_SetWindowSize(win, 1024, 768);
						break;

						//Add score
					case SDLK_5:
						SDL_SetWindowSize(win, 1280, 720);
						break;

					case SDLK_6:
						SDL_SetWindowSize(win, 1600, 900);
						
						break;
						
					case SDLK_7:
						//Mute Music
						Sound::SetVolume(0);
						break;
					case SDLK_8:
						//Decrease Volume
						Sound::SetVolume(Volume -= 10);
						break;
					case SDLK_9:
						//Increase Volume
						Sound::SetVolume(Volume += 10);
						break;
					case SDLK_0:
						//Set Music to full
						Sound::SetVolume(Volume = 128);
						break;
					
				}
			break;
		}
	}
}
// end::handleInput[]

void ResetMap()
{
	//Rows
	for (int Row = 0; Row < Map_Rows; Row++)
	{
		//Collums
		for (int collum = 0; collum < Map_Collums; collum++)
		{
			switch (Map[Row][collum])
			{
			case  PacmanGridStates::EATEN:
			{
				Map[Row][collum] = PacmanGridStates::PELLET;
				
			} break;

			case  PacmanGridStates::EATEN_BIG:
				{
					Map[Row][collum] = PacmanGridStates::BIG_PELLET;
				} break;
			}
		}
	}
}



int pixelFromGridX(int GridX)
{
	return pixelOffsetX + (GridX * pixelPerGridCell);
}

int pixelFromGridY(int GridY)
{
	return  pixelOffsetY + (GridY * pixelPerGridCell);
}

int gridFromPixelX(int pixelX)
{
	return (pixelX - pixelOffsetX) / pixelPerGridCell; //TODO integer division - check me
}

int gridFromPixelY(int pixelY)
{
	return (pixelY - pixelOffsetY) / pixelPerGridCell;
}

void collisions()
{

	//PlayerColide = Collision::RectCD( &Player, &Player2);
	if (Dead != true)
	{
		if (BigPellet == false)
		{
			if (Collision::RectCD(&Player, &Player2) || Collision::RectCD(&Player, &GhostMove[1]) || Collision::RectCD(&Player, &GhostMove[2]) || Collision::RectCD(&Player, &GhostMove[3]))
			{
			Dead = true; Died = true;
			}
		}
		if (BigPellet == true)
		{
			if (Collision::RectCD(&Player, &Player2))
			{
				ScoreMSG = true;
				Ghost_DOWN = false; Ghost_UP = false; Ghost_RIGHT = false; Ghost_LEFT = false;
				//Set callback
				SDL_TimerID timerID = SDL_AddTimer(3 * 1000, callback, "EATPlayer2");
			}
		}		
	}
	
	int gridX = gridFromPixelX(Player.x + GridCentre); //tODO softcode and check
	int gridY = gridFromPixelY(Player.y + GridCentre);

	int gridX2 = gridFromPixelX(Player2.x + GridCentre); //tODO softcode and check
	int gridY2 = gridFromPixelY(Player2.y + GridCentre);

	switch (Map[gridY][gridX])
	{

	case PacmanGridStates::BIG_PELLET:

		Map[gridY][gridX] = PacmanGridStates::EATEN_BIG;

		Sound::PlaySound(SFX_WakaWaka, 1);

		PlayerScore += 50;

		Pellets--;

		BigPellet = true;

		break;
		
	case PacmanGridStates::PELLET: //Collide with pellet
		//Change state in the grid to eaten
		Map[gridY][gridX] = PacmanGridStates::EATEN;
		//Plat SFX
		Sound::PlaySound(SFX_WakaWaka,1);
		//Incriment score
		PlayerScore += 10;
		//take 1 away from the pellet count to keep track of the level progression
		Pellets--;
		break;
		
	case PacmanGridStates::Teleport_1:
		Player.x = 625;
		break;
	case PacmanGridStates::Teleport_2:
		Player.x = 25;
		break;
	case PacmanGridStates::EMPTY:
		break;
	case PacmanGridStates::GATE:
		break;
	case PacmanGridStates::WALL:
		if (LEFT == true)
		{
			LEFT = false;
			Player.x += WallOffset;
		}
		if (RIGHT == true)
		{
			RIGHT = false;
			Player.x -= WallOffset;
		}
		if (UP == true)
		{
			UP = false;
			Player.y += WallOffset;
		}
		if (DOWN == true)
		{
			DOWN = false;
			Player.y -= WallOffset;
		}
		break;

	default:
		break;
	
	}
	switch (Map[gridY2][gridX2])
	{
	case PacmanGridStates::Teleport_1:
		Player2.x = 625;
		break;
	case PacmanGridStates::Teleport_2:
		Player2.x = 25;
		break;
	case PacmanGridStates::EMPTY:
		break;
	case PacmanGridStates::GATE:
		break;
	case PacmanGridStates::WALL:
		if (Ghost_LEFT == true)
		{
			Ghost_LEFT = false;
			Player2.x += WallOffset;
		}
		if (Ghost_RIGHT == true)
		{
			Ghost_RIGHT = false;
			Player2.x -= WallOffset;
		}
		if (Ghost_UP == true)
		{
			Ghost_UP = false;
			Player2.y += WallOffset;
		}
		if (Ghost_DOWN == true)
		{
			Ghost_DOWN = false;
			Player2.y -= WallOffset - 7;
		}
		break;

	default:
		break;

	}

}


// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
	//Reset Pellets
	if (Reset == true)
	{
		ResetMap();
		Pellets = 244;
		Reset = false;
	}
	//Pause Menu ON
	if (Pause == true)
	{
		//Freeze Movement
		UP = false; DOWN = false; LEFT = false; RIGHT = false;
		Ghost_UP = false; Ghost_DOWN = false; Ghost_RIGHT = false; Ghost_LEFT = false;
	}
	//Movement------------------------------------------------
	if (Game == true && UP == true)
	{
		Player.y -= PlayerSpeed;
		Animation.x = 1515;Animation.y = 158;	
	}
	if (Game == true && DOWN == true)
	{
		Player.y += PlayerSpeed;
		Animation.x = (1515 + 38);Animation.y = 158;
	}
	if (Game == true && RIGHT == true)
	{
		Player.x += PlayerSpeed;
		Animation.x = (1515 + 38);Animation.y = 0;
	}
	if (Game == true && LEFT == true)
	{
		Player.x -= PlayerSpeed;
		Animation.x = 1515; Animation.y = 0;
	}


	if (Game == true && Ghost_UP == true)
	{
		Player2.y -= PlayerSpeed;
		if (BigPellet == false)
		{
			GhostAnimation[0].y = 242;
		}
	}
	if (Game == true && Ghost_DOWN == true)
	{
		Player2.y += PlayerSpeed;
		if (BigPellet == false)
		{
			GhostAnimation[0].y = 79;
		}		
	}
	if (Game == true && Ghost_RIGHT == true)
	{
		Player2.x += PlayerSpeed;
		if (BigPellet == false)
		{
			GhostAnimation[0].y = 0;
		}
	}
	if (Game == true && Ghost_LEFT == true)
	{
		Player2.x -= PlayerSpeed;
		if (BigPellet == false)
		{
			GhostAnimation[0].y = 165;
		}
	}

	if (Game == true && BigPellet == true)
	{
		GhostAnimation[0].x = 1266; GhostAnimation[1].x = 1266; GhostAnimation[2].x = 1266; GhostAnimation[3].x = 1266;
		//Mix_PlayChannel(-1, SFX_EatingGhost, );
		Sound::PlaySound(SFX_BigPellet, 2);	

		//Set callback
		SDL_TimerID timerID = SDL_AddTimer(6 * 1000, callback, "BigPellet");
	}
	if (Game == true && BigPellet == false)
	{
		GhostAnimation[0].x = RedGhost_x;
		GhostAnimation[1].x = PinkGhost_x;
		GhostAnimation[2].x = CyanGhost_x;
		GhostAnimation[3].x = OrangeGhost_x;
	}
	//Win State
	if (Game == true && Pellets == 0)
	{
		//Timer------------- 
		LEFT = false;UP = false;RIGHT = false;DOWN = false;
		//play animation--------------

		//reset everything
		//Reset Level
		Reset = true;
		//Incriment Level
		Level++;
		//ghost position
		SetPositions();
		
	}
	if (Dead == true)
	{
		//Freeze Movement
		UP = false; DOWN = false; LEFT = false; RIGHT = false;
		Ghost_UP = false; Ghost_DOWN = false; Ghost_RIGHT = false; Ghost_LEFT = false;
		//Play Sound Effect once.
		
		if (tmp == true){Sound::PlaySound(SFX_Dies, 4);	tmp = false;}

		//Set callback for 
		SDL_TimerID timerID = SDL_AddTimer(3 * 1000, callback, "Dead");

	}
	if (Died == true)
	{
		Lives--;
		Died = false;
	}

	collisions();

	if (OpeningSong == true)
	{	
		//Mix_PlayChannel(-1, SFX_OpeningSong, 0);	
		Sound::PlaySound(SFX_OpeningSong, -1);
		printf("Playing Opening Song \n");
		OpeningSong = false;	
	}


}

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
		Uint32 Ghost = (ticks / 200) % 2;
		Uint32 Death = (ticks / 300) % 13;


		if (Game == true)
		{
			//5 Second Delay before the game start
			GameTimer++;
			if (GameTimer <  220)
			{	
				UP = false;DOWN = false;RIGHT = false;LEFT = false;
				Ghost_UP = false; Ghost_DOWN = false; Ghost_RIGHT = false; Ghost_LEFT = false;

				//Draw Ready and player text for a short time
				Text::DrawText(ren, messageTexture[3], 225, 330, 250, 50);
				Text::DrawText(ren, messageTexture[4], 300, 475, 100, 50);
				
				if (GameTimer == 1)
				{
					OpeningSong = true;
				}				
			}
			else
			{
				Music = true;
			}

			//28 blocks wide

			//Draw the Score and High Score
			// DrawScore   Render,Texture,		X,	Y,	W,	H
			Score::DrawScore(ren, ScoreTexture, 200, 45, 60, 20);
			Score::DrawScore(ren, HScoreTexture, 370, 45, 60, 20);

			//Drawing Text
			// DrawText Function, MessageTex,		 X , Y, W, H,
			Text::DrawText(ren, messageTexture[0], 275, 0, 150, 40);
			Text::DrawText(ren, messageTexture[Ghost + 1], 180, 0, 50, 40);


			//Drawing Sprites
			//			Screen,Img,Source Rectangle, Destination Rectangle
			//Background
			Sprite::Draw(ren, tex, 600, 0, 600, 656, 5, 75, 685, 745);

			//Rows
			for (int Row = 0; Row < Map_Rows; Row++)
			{
				//Collums
				for (int collum = 0; collum < Map_Collums; collum++)
				{
					switch (Map[Row][collum])
					{	
					case  PacmanGridStates::PELLET:
						{
							//Draw(Yummy)
							Sprite::Draw(ren, tex, 26, 47, 12, 12, pixelFromGridX(collum), pixelFromGridY(Row), 12, 12);
						} break;

					case  PacmanGridStates::BIG_PELLET:
						{
							//Draw(Yummy)
							Sprite::Draw(ren, tex, 18 + (Ghost* 40), 61, 25, 25, pixelFromGridX(collum) - BIG_PELLET_Offset, pixelFromGridY(Row) - BIG_PELLET_Offset, 25, 25);
						} break;
					}
				}
			}
			
			//Player2 	Player2.x = 325;Player2.y = 300;
			Sprite::Draw(ren, tex, GhostAnimation[0].x, GhostAnimation[0].y + (Ghost * 40), 40, 40, Player2.x, Player2.y, Player2.w, Player2.h);
			//Ghosts
			Sprite::Draw(ren, tex, GhostAnimation[1].x, GhostAnimation[1].y +( Ghost * 40), 40, 40, GhostMove[0].x, GhostMove[0].y, GhostMove[0].w, GhostMove[0].w);
			Sprite::Draw(ren, tex, GhostAnimation[2].x, GhostAnimation[2].y +( Ghost * 40), 40, 40, GhostMove[1].x, GhostMove[1].y, GhostMove[1].w, GhostMove[1].w);
			Sprite::Draw(ren, tex, GhostAnimation[3].x, GhostAnimation[2].y +( Ghost * 40), 40, 40, GhostMove[2].x, GhostMove[2].y, GhostMove[2].w, GhostMove[2].w);
			//Sprite::Draw(ren, tex, GhostAnimation[3].x, GhostAnimation[3].y + (Ghost * 40), 40, 40, 380, 400, 40, 40);

			if (ScoreMSG == true)
			{
				Sprite::Draw(ren, tex, 1655,332 , 40, 40, Player2.x, Player2.y,50 ,50);
				GhostAnimation[0].y = 0; GhostAnimation[0].x = 1200;
			}
			if (Dead == true)
			{			
				Sprite::Draw(ren, tex, 1472, 0 + (Death * 40), 38, 38, Player.x, Player.y, Player.w, Player.h);
				//Game over text
				if (Lives <= 0)
				{
					Text::DrawText(ren, messageTexture[5], 275, 475, 150, 50);
				}
			}
			else
			{
			//Pacman
			Sprite::Draw(ren, tex, Animation.x, Animation.y + (Pacman * 40), 38,  38, Player.x, Player.y, Player.w, Player.h);
			}

			//Level  
			if (Level > 0)
			{	//Cherry
				Sprite::Draw(ren, tex, 1390, 0, 38, 38, 600, 830, 42, 42);
			}
			if (Level > 1)	{Sprite::Draw(ren, tex, 1390, 40, 38, 38, 550, 830, 42, 42);}
			if (Level > 2)	{Sprite::Draw(ren, tex, 1390, 80, 38, 38, 500, 830, 42, 42);}
			if (Level > 3) { Sprite::Draw(ren, tex, 1390, 120, 38, 38, 450, 830, 42, 42); }
			if (Level > 4) { Sprite::Draw(ren, tex, 1390, 160, 38, 38, 400, 830, 42, 42); }
			

			//Lives
			if (Lives > 1)	{Sprite::Draw(ren, tex, 1515, 40, 38, 38, 50 ,830, 42, 42);	}
			if (Lives > 2)	{Sprite::Draw(ren, tex, 1515, 40, 38, 38, 100, 830, 42, 42);}
			if (Lives > 3)	{Sprite::Draw(ren, tex, 1515, 40, 38, 38, 150, 830, 42, 42);}
			if (Lives > 4) { Sprite::Draw(ren, tex, 1515, 40, 38, 38, 200, 830, 42, 42); }
			
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
			GameTimer = 0;
			//Drawing Characters next to there text
			Sprite::Draw(ren, tex, 1758, Ghost * 40, 40, 40, 150, 200, 40, 40);
			Sprite::Draw(ren, tex, 1675, Ghost * 40, 40, 40, 150, 300, 40, 40);
			Sprite::Draw(ren, tex, 1717, Ghost * 40, 40, 40, 150, 400, 40, 40);
			Sprite::Draw(ren, tex, 1635, Ghost * 40, 40, 40, 150, 500, 40, 40);

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
	messageTexture[5] = Text::LoadText("./assets/Fonts/Hack-Regular.ttf", "GAMEOVER!", 150, 255, 0, 0, ren);

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
	Player.x = Start_X;	Player.y = Start_Y; Player.w = 42; Player.h = 42;
	Player2.x = Start_X2;	Player2.y = Start_Y2; Player2.w = 40; Player2.h = 40;
	//Set Players intial position
	Animation.x = 1515;	Animation.y = 0;
	
	GhostAnimation[0].x = RedGhost_x;
	GhostAnimation[1].x = PinkGhost_x;
	GhostAnimation[2].x = CyanGhost_x;
	GhostAnimation[3].x = OrangeGhost_x;

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
	SFX_WakaWaka = Sound::LoadSFX("./assets/Sound/PacmanWakaWaka2.Wav");

	SFX_EatingGhost = Sound::LoadSFX("./assets/Sound/Pacman Eating Ghost.Wav");

	SFX_Dies = Sound::LoadSFX("./assets/Sound/Pacman Dies.Wav");

	SFX_OpeningSong = Sound::LoadSFX("./assets/Sound/Pacman Opening Song.mp3");

	SFX_BigPellet = Sound::LoadSFX("./assets/Sound/large_pellet_loop.Wav");

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Sounds added");
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

void init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;	cleanExit(1);
	}
	std::cout << "SDL initialised OK!\n";

	//Initialize SDL_mixer http://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
	//Sound Frequency, Sample format, Hardware channels
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;	cleanExit(1);
	}
	//create window
	win = SDL_CreateWindow("Pacman", 300, 100, ScreenSize_X, ScreenSize_Y, SDL_WINDOW_SHOWN);

	//error handling
	if (win == nullptr){	std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;	cleanExit(1);	}

	std::cout << "SDL CreatedWindow OK!\n";

	//Initialize SDL_ttf
	if (TTF_Init() == -1){	cleanExit(1);	}

	//turning V Sync On 
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)	{
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
