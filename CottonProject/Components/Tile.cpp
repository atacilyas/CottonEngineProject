#include "Tile.h"

Tile::Tile()
{
	m_TileRect = { 0,0,0,0 };
}

Tile::Tile(SDL_Rect clipping)
	:m_TileRect(clipping)
{
}


Tile::~Tile()
{
}

bool Tile::BackgroundInitialize()
{

	return true;
}

void Tile::BackgroundUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

void Tile::BackgroundEvent(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);
}

void Tile::BackgroundDraw()
{

}