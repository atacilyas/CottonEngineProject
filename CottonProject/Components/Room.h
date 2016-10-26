#pragma once
#include <SDL.h>
class Room
{
public:
	Room(SDL_Rect size);
	~Room();

	SDL_Rect Size;
	int id;
};

