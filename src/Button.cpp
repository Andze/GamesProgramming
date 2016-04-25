#include "Button.h"


bool Button::CreateButton(int x, int y, int w, int h, SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int Mouse_x, Mouse_y;
		SDL_GetMouseState(&Mouse_x, &Mouse_y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (Mouse_x < x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (Mouse_x > x + w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (Mouse_y < y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (Mouse_y > y + h)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
		
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				
				break;

			case SDL_MOUSEBUTTONDOWN:
				SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Clicked");

				return false;
		
				break;

			case SDL_MOUSEBUTTONUP:
				
				break;
			}
				

		}

	
	}
	return true;
}
	

Button::Button()
{
}


Button::~Button()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Buttons created Loaded");
}

