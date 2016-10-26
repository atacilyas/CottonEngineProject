#pragma once
#include "../../CottonEngine/BaseScene.h"
#include "../../CottonEngine/stdafx.h"
#include "../../CottonEngine/Components/CameraComponent.h"
#include "../../CottonEngine/Components/TextComponent.h"
#include "../../CottonEngine/Components/ButtonComponent.h"
#include "../../CottonEngine/Helpers/Timer.h"

class TestLevel : public BaseScene
{
public:
	TestLevel();
	~TestLevel();

	bool Initialize();
	void Update(float deltatime);
	void Draw();
	void Event(SDL_Event e);
	void OnPaused();
private:
};

