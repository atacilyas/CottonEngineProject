#include "MapLevel.h"
#include "../../CottonEngine/stdafx.h"
#include "../Components/Room.h"
#include <string>
MapLevel::MapLevel()
	:BaseScene()
{
}


MapLevel::~MapLevel()
{
}

bool MapLevel::Initialize()
{
	cout << "initialize scene" << endl;

	auto cam = new CameraComponent();
	AddChild(cam);
	cam->SetActive();

	m_BackgroundColor = { 97,171,90, 255 };

	m_Map = new TileMap(DOUBLE2(736, 544));
	AddChild(m_Map);

	GenerateMap();
	return true;
}
void MapLevel::Update(float deltatime)
{
	float speed = 0.7f;
	UNREFERENCED_PARAMETER(deltatime);
	if (Input::GetInstance()->GetKey(SDLK_a))
	{
		GetCamera()->GetTransform()->Move(-speed, 0);
	}
	if (Input::GetInstance()->GetKey(SDLK_d))
	{
		GetCamera()->GetTransform()->Move(speed, 0);
	}
	if (Input::GetInstance()->GetKey(SDLK_w))
	{
		GetCamera()->GetTransform()->Move(0,-speed);
	}
	if (Input::GetInstance()->GetKey(SDLK_s))
	{
		GetCamera()->GetTransform()->Move(0, speed);
	}

}

void MapLevel::Draw()
{
}

void MapLevel::Event(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);

	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == SDLK_r)
		{
			GenerateMap();
		}
	}
}

void MapLevel::OnPaused()
{
}

void MapLevel::GenerateMap()
{

	m_Map->AddTileSet("Floor", "Rescources/Sprites/Rouge/Objects/Floor.png");
	m_Map->AddTileSet("Wall", "Rescources/Sprites/Rouge/Objects/Wall.png");

	vector<Room> rooms = { Room(SDL_Rect{0,0,45,33}) };
	vector<Room> newrooms;
	int minWidth = 6;
	int minHeight = 6;

	//split regions
	for (size_t i = 0; i < 10; i++)
	{
		for each (Room room in rooms)
		{
			if (rand()%2 == 0)
			{
				int x = room.Size.x + (rand() % (room.Size.w - room.Size.x));
				if (x > room.Size.x + minWidth && x < room.Size.w - minWidth)
				{
					Room a(SDL_Rect{ room.Size.x ,room.Size.y ,x,room.Size.h });
					a.id = rand() % 3;
					Room b(SDL_Rect{ x ,room.Size.y ,room.Size.w ,room.Size.h });
					b.id = rand() % 3;
					newrooms.push_back(a);
					newrooms.push_back(b);
				}
				else
				{
					newrooms.push_back(room.Size);
				}
			}
			else
			{
				int y = room.Size.y + (rand() % (room.Size.h - room.Size.y));
				if (y > room.Size.y + minHeight && y < room.Size.h - minHeight)
				{
					Room a(SDL_Rect{ room.Size.x ,room.Size.y ,room.Size.w,y });
					a.id = rand() % 3;
					Room b(SDL_Rect{ room.Size.x ,y ,room.Size.w,room.Size.h });
					b.id = rand() % 3;
					newrooms.push_back(a);
					newrooms.push_back(b);
				}
				else
				{
					newrooms.push_back(room.Size);
				}
			}

		}
		rooms = newrooms;
		newrooms.clear();
	}

	newrooms.clear();

	for (int x = 0; x < 46; x++)
	{
		for (int y = 0; y < 34; y++)
		{
			DOUBLE2 type(6, 0);

			int id = 0;
			for each (Room var in rooms)
			{
				if (x < var.Size.w && x > var.Size.x && y < var.Size.h && y > var.Size.y)
				{
					id = var.id;
					if (x == var.Size.x + 1)
					{
						if (y == var.Size.y + 1)
						{
							type.x = 0;
							type.y = 0;
						}
						else if (y == var.Size.h - 1)
						{
							type.x = 0;
							type.y = 2;
						}
						else
						{
							type.x = 0;
							type.y = 1;
						}

					}
					else if (x == var.Size.w - 1)
					{
						if (y == var.Size.y + 1)
						{
							type.x = 2;
							type.y = 0;
						}
						else if (y == var.Size.h - 1)
						{
							type.x = 2;
							type.y = 2;
						}
						else
						{
							type.x = 2;
							type.y = 1;
						}

					}
					else if (y == var.Size.y + 1)
					{
						type.x = 1;
						type.y = 0;
					}
					else if (y == var.Size.h - 1)
					{
						type.x = 1;
						type.y = 2;
					}
					else
					{
						type.x = 1;
						type.y = 1;
					}
				}
			}


			SDL_Rect clippingRect = { (int)type.x  * (128 / 8),(int)type.y* (144 / 9),128 / 8,144 / 9 };
			SDL_Rect destRect = { x * (128 / 8),y* (144 / 9),128 / 8,144 / 9 };

			//from surface //from rect //to surface //to rect
			m_Map->AddTile("Floor", clippingRect, destRect, true);
		}
	}


	for each (Room var in rooms)
	{
		Room a = var;
		a.Size.x = a.Size.x + (rand() % (a.Size.w - minWidth - a.Size.x));
		a.Size.y = a.Size.y + (rand() % (a.Size.h - minHeight - a.Size.y));

		a.Size.w = a.Size.x + minWidth + (rand() % (a.Size.w - minWidth - a.Size.x));
		a.Size.h = a.Size.y + minHeight + (rand() % (a.Size.h -minHeight - a.Size.y));

		a.id = rand() % 24;
		newrooms.push_back(a);
	}
	rooms = newrooms;

	for (int x = 0; x < 46; x++)
	{
		for (int y = 0; y < 34; y++)
		{
			DOUBLE2 type(6, 0);

			int id = 0;
			for each (Room var in rooms)
			{
				if (x < var.Size.w && x > var.Size.x && y < var.Size.h && y > var.Size.y)
				{
					id = var.id;
					if (x == var.Size.x +1 )
					{
						if (y == var.Size.y + 1)
						{
							type.x = 0;
							type.y = 0;
						}
						else if (y == var.Size.h - 1)
						{
							type.x = 0;
							type.y = 2;
						}
						else
						{
							type.x = 0;
							type.y = 1;
						}
						
					}
					else if (x == var.Size.w - 1)
					{
						if (y == var.Size.y + 1)
						{
							type.x = 2;
							type.y = 0;
						}
						else if (y == var.Size.h - 1)
						{
							type.x = 2;
							type.y = 2;
						}
						else
						{
							type.x = 2;
							type.y = 1;
						}
						
					}
					else if (y == var.Size.y + 1)
					{
						type.x = 1;
						type.y = 0;
					}
					else if (y == var.Size.h - 1)
					{
						type.x = 1;
						type.y = 2;
					}
					else
					{
						type.x = 1;
						type.y = 1;
					}
				}
			}
			type.x += ((id % 3) * 7);
			type.y += (floor(id / 3) +1) * 3;

			
			SDL_Rect clippingRect = { (int)type.x  * (128 / 8),(int)type.y* (144 / 9),128 / 8,144 / 9 };
			SDL_Rect destRect = { x * (128 / 8),y* (144 / 9),128 / 8,144 / 9 };

			//from surface //from rect //to surface //to rect
			m_Map->AddTile("Floor", clippingRect, destRect,false);
		}
	}
	DOUBLE2 t = m_Map->GetSize();
	GetChild<TileMap>()->GetTransform()->Translate((float)t.x/2.0f, (float)t.y/2.0f);
}