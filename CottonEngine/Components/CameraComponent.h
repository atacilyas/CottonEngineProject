#pragma once
#include "../stdafx.h"
#include "BaseComponent.h"

class CameraComponent :public BaseComponent
{
public:
	CameraComponent();
	~CameraComponent();

	bool BackgroundInitialize();
	void BackgroundUpdate(float deltatime);
	void BackgroundEvent(SDL_Event e);
	void BackgroundDraw();

	void SetActive();
private:
	DOUBLE2 m_WindowSize;
};

