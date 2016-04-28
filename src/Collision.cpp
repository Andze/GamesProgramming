#include "Collision.h"

/* Checks if a collision has happened between obj1 and obj2 */
bool Collision::RectCD(SDL_Rect *obj1, SDL_Rect *obj2)
{
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = obj1->x;
	left2 = obj2->x;
	right1 = obj1->x + obj1->w;
	right2 = obj2->x + obj2->w;
	top1 = obj1->y;
	top2 = obj2->y;
	bottom1 = obj1->y + obj1->h;
	bottom2 = obj2->y + obj2->h;

	if (bottom1 < top2)
	{
		return(false);
	}
	if (top1 > bottom2)
	{
		return(false);
	}

	if (right1 < left2)
	{
		return(false);
	}
	if (left1 > right2)
	{
		return(false);
	}

	return(true);
}

/* Checks if a collision has happened between objects using coordinates */
bool Collision::Coords(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = x1;
	left2 = x2;
	right1 = x1 + w1;
	right2 = x2 + w2;
	top1 = y1;
	top2 = y2;
	bottom1 = y1 + h1;
	bottom2 = y2 + h2;

	if (bottom1 <= top2)
	{
		return(false);
	}
	if (top1 >= bottom2)
	{
		return(false);
	}

	if (right1 <= left2)
	{
		return(false);
	}
	if (left1 >= right2)
	{
		return(false);
	}

	return(true);
}
Collision::Collision()
{
}


Collision::~Collision()
{
}
