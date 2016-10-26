#pragma once
#include "..\..\CottonEngine\Components\BaseComponent.h"

class Tile : public BaseComponent
{
public:
	Tile();
	Tile(SDL_Rect clipping);
	~Tile();

	bool BackgroundInitialize();
	void BackgroundUpdate(float deltatime);
	void BackgroundEvent(SDL_Event e);

private:
	void BackgroundDraw();
	SDL_Rect m_TileRect;
};

