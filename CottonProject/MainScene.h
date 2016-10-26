#pragma once
#include "../CottonEngine/MainClass.h"
#include <vector>

class MainScene : public MainClass
{
public:
	MainScene();
	~MainScene();

	bool Initialize();
	void Event(SDL_Event e);
};

