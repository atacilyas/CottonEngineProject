#pragma once
#include "stdafx.h"
#include <vector>

class Timer;
class Window;
class MainClass
{
public:
	MainClass();
	~MainClass();

	//start up the game
	void InitializeGameLoop();

protected:
	//manage windows
	void AddWindow(Window *newscene);
	vector<Window *>m_WindowList;

	//gameloop to add in game()
	virtual bool Initialize() = 0;
	virtual void Event(SDL_Event e) = 0;

	bool m_QuitGame;
	bool m_PauseOnWindowFocus;
private:
	void GameLoop();

	Timer* m_DeltaTime;
};

