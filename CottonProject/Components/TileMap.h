#pragma once
#include "..\..\CottonEngine\Components\BaseComponent.h"
#include "..\..\CottonEngine\Components\TextureComponent.h"
#include <map>

class TileMap :	public BaseComponent
{
public:
	TileMap(DOUBLE2 size);
	~TileMap();

	bool BackgroundInitialize();
	void BackgroundUpdate(float deltatime);
	void BackgroundEvent(SDL_Event e);
	void AddTileSet(string name,string path);
	void AddTile(string tileset, SDL_Rect from, SDL_Rect to, bool clear = false);
	void UpdateTexture() {m_texture->LoadTexture(m_Surface);}
	DOUBLE2 GetSize() { return m_texture->GetSize() * GetTransform()->GetScale(); }
	void SetSize(DOUBLE2 size) { m_MapSize = size; }
	SDL_Color GetPixel(int x, int y);
private:
	void BackgroundDraw();

	SDL_Surface* m_Surface;
	TextureComponent* m_texture;
	map<string,SDL_Surface*> m_TileSets;
	DOUBLE2 m_MapSize;
};

