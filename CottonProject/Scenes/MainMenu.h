#pragma once
#include "../../CottonEngine/BaseScene.h"
#include "../../CottonEngine/stdafx.h"
#include "../../CottonEngine/Components/CameraComponent.h"
#include "../../CottonEngine/Components/TextComponent.h"
#include "../../CottonEngine/Components/ButtonComponent.h"
#include "../../CottonEngine/Helpers/Timer.h"

class MainMenu : public BaseScene
{
public:
	MainMenu();
	~MainMenu();

	bool Initialize();
	void Update(float deltatime);
	void Draw();
	void Event(SDL_Event e);
	void OnPaused();
	TextComponent* m_pText;
	ButtonComponent* m_pButton;
	Timer time,test;
private:
};

