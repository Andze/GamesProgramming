#include "Score.h"

Score::Score()
{
}


TTF_Font* Score::LoadFont(char* File, int size)
{
	TTF_Font* font = TTF_OpenFont(File, size);
	if (font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

	}

	return font;
}

SDL_Texture* Score::LoadScore(TTF_Font* Font, int Score, int R, int G, int B, SDL_Renderer* Render)
{
	SDL_Color Color = { R, G, B };

	SDL_Surface* Surf_Temp = nullptr;
	SDL_Texture* Tex_Return = nullptr;

	std::stringstream Pscore;
	Pscore << Score;
	
	Surf_Temp = TTF_RenderText_Solid(Font, Pscore.str().c_str(), Color);
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

bool Score::DrawScore(SDL_Renderer* ren, SDL_Texture* tex, int x, int y, int w, int h)
{
	if (ren == nullptr || tex == NULL) {
		return false;
	}

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;
	destR.w = w;
	destR.h = h;

	SDL_RenderCopy(ren, tex, NULL, &destR);

	return true;
}

int Score::LoadHighscore(char* File,int Score)
{

	SDL_RWops* file = SDL_RWFromFile(File, "r");

	//File does not exist
	if (file == nullptr)
	{
		printf("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());

		//Create file for writing
		file = SDL_RWFromFile(File, "w");
		if (file != NULL)
		{
			printf("New file created!\n");

			SDL_RWwrite(file, 0, sizeof(Score), 1);

			//Close file handler
			SDL_RWclose(file);
		}
		else
		{
			printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
		}
	}
	//File exists
	else
	{
		//Load data
		printf("Reading file...!\n");

		SDL_RWread(file, &Score, sizeof(Score), 1);

		//Close file handler
		SDL_RWclose(file);
	}

	return Score;
}

bool Score::SaveHighScore(char* File, int Score, int HighScore)
{
	//Open data for writing
	SDL_RWops* file = SDL_RWFromFile(File, "w");
	if (file != nullptr)
	{
		if (Score >= HighScore)
		{
			HighScore = Score;
		}

		//Save data
		SDL_RWwrite(file, &HighScore, sizeof(HighScore), 1);

		//Close file handler
		SDL_RWclose(file);
	}
	else
	{
		printf("Error: Unable to save file! %s\n", SDL_GetError());
	}

	return true;
}


Score::~Score()
{
}
