#pragma once
#include "../../CottonEngine/BaseScene.h"
#include "../../CottonEngine/stdafx.h"
#include "../../CottonEngine/Components/CameraComponent.h"
#include "../../CottonEngine/Components/TextComponent.h"
#include "../../CottonEngine/Components/TextureComponent.h"
#include "../../CottonEngine/Helpers/Timer.h"

class SplashScreen : public BaseScene
{
public:
	SplashScreen();
	~SplashScreen();

	bool Initialize();
	void Update(float deltatime);
	void Draw();
	void Event(SDL_Event e);
	void OnPaused();

	TextComponent* m_pText;
	TextureComponent* m_pDrawing;
	Timer time,pausetimer;
private:
};

