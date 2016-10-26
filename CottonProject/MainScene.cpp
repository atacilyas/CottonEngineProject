#include "MainScene.h"
#include "../CottonEngine/stdafx.h"
#include "../CottonEngine/Window.h"
#include "Scenes\SplashScreen.h"
#include "Scenes\MainMenu.h"
#include "Scenes\TestLevel.h"
#include "Scenes\MapLevel.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

bool MainScene::Initialize()
{
	auto mainWindow = new Window(DOUBLE2(736, 544));
	AddWindow(mainWindow);
	//mainWindow->AddScene(new MapLevel());
	//mainWindow->AddScene(new TestLevel());

	mainWindow->AddScene(new SplashScreen());
	mainWindow->AddScene(new MainMenu());
	m_PauseOnWindowFocus = true;
	return true;
}

void MainScene::Event(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
	{
		cout << "shutting down" << endl;
		m_QuitGame = true;
 	}
}