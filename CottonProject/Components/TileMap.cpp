#include "TileMap.h"
#include "Tile.h"

TileMap::TileMap(DOUBLE2 size)
	:BaseComponent()
	,m_MapSize(size)
{
	m_Type = typeid(this).name();
	m_texture = new TextureComponent();

	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	m_Surface = SDL_CreateRGBSurface(0,(int)m_MapSize.x,(int)m_MapSize.y, 32, rmask, gmask, bmask, amask);
	if (m_Surface == NULL) {
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
	}
}


TileMap::~TileMap()
{
	for each (auto var in m_TileSets)
	{
		if (var.second != nullptr)
		{
			SDL_FreeSurface(var.second);
		}
	}
}

bool TileMap::BackgroundInitialize() 
{
	AddChild(m_texture);
	UpdateTexture();
	return true;
}

void TileMap::BackgroundUpdate(float deltatime) 
{
	UNREFERENCED_PARAMETER(deltatime);
}

void TileMap::BackgroundEvent(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);
	if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			m_texture->SetActive(!m_texture->GetActive());
			break;
		default:
			break;
		}
	}
}

void TileMap::BackgroundDraw()
{
	UpdateTexture();
}

void TileMap::AddTileSet(string name,string path)
{
	m_TileSets[name] = IMG_Load(path.c_str());
	if (m_TileSets[name] == NULL)
	{
		m_TileSets.erase(name);
		cout << "TextureComponent::Initialize loading image failed" << endl;
	}
}

void TileMap::AddTile(string tileset, SDL_Rect from, SDL_Rect to,bool clear)
{
	if (clear)
	{
		SDL_FillRect(m_Surface, &to, 0x000000);
	}

	SDL_BlitSurface(m_TileSets[tileset], &from, m_Surface, &to);
}

SDL_Color TileMap::GetPixel(int x,int y)
{
	Uint32 *pixels = (Uint32 *)m_Surface->pixels;
	//Get the requested pixel
	Uint32 res =pixels[(y * m_Surface->w) + x];
	SDL_Color col;
	SDL_GetRGBA(res, m_Surface->format, &col.r, &col.g, &col.b, &col.a);

	return col;
}