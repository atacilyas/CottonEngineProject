#pragma once
#include "../../CottonEngine/BaseScene.h"
#include "../../CottonEngine/stdafx.h"
#include "../../CottonEngine/Components/CameraComponent.h"
#include "../../CottonEngine/Components/TextComponent.h"
#include "../../CottonEngine/Components/ButtonComponent.h"
#include "../../CottonEngine/Helpers/Timer.h"
#include "../Components/TileMap.h"
class MapLevel : public BaseScene
{
public:
	MapLevel();
	~MapLevel();

	bool Initialize();
	void Update(float deltatime);
	void Draw();
	void Event(SDL_Event e);
	void OnPaused();
private:
	TileMap* m_Map;

	void GenerateMap();
};

