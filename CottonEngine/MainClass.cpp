
#include "MainClass.h"
#include "BaseScene.h"
#include "Helpers/Timer.h"
#include "../Window.h"
MainClass::MainClass()
	:m_QuitGame(false)
	,m_PauseOnWindowFocus(false)
{
	m_DeltaTime = new Timer();
}


MainClass::~MainClass()
{
	for (size_t i = 0; i < m_WindowList.size(); i++)
	{
		SafeDelete(m_WindowList.at(i));
	}

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	
	SafeDelete(m_DeltaTime);
}

void MainClass::InitializeGameLoop()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Set neirest neighbor scaling
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
		{
			printf("Warning: neirest neighbor texture filtering not enabled!");
		}

		//set loading from PNG
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError());
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		//Initialize SDL_ttf
		if (TTF_Init() < 0)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}

		//start the gameloop
		GameLoop();
	}
}

void MainClass::GameLoop()
{
	//initialize main scene
	if (Initialize())
	{

		SDL_Event e;
		//reset delta timer
		m_DeltaTime->Start();
		while (!m_QuitGame)
		{
			m_DeltaTime->Start();
			//if there are no more windows open shutdown
			if (m_WindowList.size() > 0)
			{
				int i = m_WindowList.at(0)->GetAmountOfWindows();
				if (i <= 0)
					m_QuitGame = true;
			}
			else
			{
				m_QuitGame = true;
			}

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//handle mainscene event
				Event(e);

				//handle window events
				for (size_t i = 0; i < m_WindowList.size(); i++)
				{
					m_WindowList.at(i)->handleEvent(e);
				}

				//handle input
				if (e.type == SDL_KEYDOWN)
				{
					Input::GetInstance()->SetKeyDown(e.key.keysym.sym);
				}
				else if (e.type == SDL_KEYUP)
				{
					Input::GetInstance()->SetKeyUp(e.key.keysym.sym);
				}
			}

			for (size_t i = 0; i < m_WindowList.size(); i++)
			{
				//handle window gameloops
				if (m_WindowList.at(i)->HasKeyboardFocus() || !m_PauseOnWindowFocus)
				{
					m_DeltaTime->Pause(false);
					m_WindowList.at(i)->Update((float)m_DeltaTime->GetTicks());
					m_WindowList.at(i)->Draw();
				}
				else
				{
					m_DeltaTime->Pause();
				}
			}
		}
		Input::GetInstance()->destroy();
	}
}

void MainClass::AddWindow(Window *window)
{
	if (window->Initialize())
	{
		m_WindowList.push_back(window);
	}
	else
	{
		SafeDelete(window);
	}
}