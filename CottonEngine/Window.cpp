#include "stdafx.h"
#include "Window.h"
#include <string>
#include "BaseScene.h"
//#include "Managers\WindowManager.h"

int Window::m_WindowAmount = 0;

Window::Window(DOUBLE2 size)
{
	//Initialize non-existant window
	m_Window = NULL;
	m_Renderer = NULL;

	m_MouseFocus = false;
	m_KeyboardFocus = false;
	m_FullScreen = false;
	m_Shown = false;
	m_WindowID = -1;

	m_ScreenSize = size;
	m_CurrentScene = 0;
	m_WindowAmount++;
}
Window::~Window()
{
	if (m_Window != NULL)
	{
		SDL_DestroyWindow(m_Window);
	}

	for (size_t i = 0; i < m_SceneList.size(); i++)
	{
		SafeDelete(m_SceneList[i]);
	}

	m_MouseFocus = false;
	m_KeyboardFocus = false;
}

bool Window::Initialize()
{
	//Create window
	m_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)m_ScreenSize.x, (int)m_ScreenSize.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_Window != NULL)
	{
		m_MouseFocus = true;
		m_KeyboardFocus = true;

		//Create renderer for window
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (m_Renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(m_Window);
			m_Window = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Grab window identifier
			m_WindowID = SDL_GetWindowID(m_Window);

			//Flag as opened
			m_Shown = true;
		}
	}
	else
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}

	return m_Window != NULL && m_Renderer != NULL;
}

void Window::handleEvent(SDL_Event& e)
{
	//If an event was detected for this window
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == (uint32_t)m_WindowID)
	{
		//window event management
		switch (e.window.event)
		{
			//Window appeared
		case SDL_WINDOWEVENT_SHOWN:
			m_Shown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			m_Shown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			m_ScreenSize.x = e.window.data1;
			m_ScreenSize.y = e.window.data2;
			SDL_RenderPresent(m_Renderer);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(m_Renderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			m_MouseFocus = true;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			m_MouseFocus = false;
			break;

			//Keyboard focus gained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			m_KeyboardFocus = true;
			break;

			//Keyboard focus lost
		case SDL_WINDOWEVENT_FOCUS_LOST:
			m_KeyboardFocus = false;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			m_Minimized = true;
			m_SceneList.at(m_CurrentScene)->OnPaused();
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			m_Minimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			m_Minimized = false;
			break;

			//Hide on close
		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(m_Window);
			m_WindowAmount--;
			break;
		}
	}
	else if (e.window.windowID == (uint32_t)m_WindowID)
	{
		//event scene
		if (m_SceneList.size() > 0)
			m_SceneList.at(m_CurrentScene)->RootEvent(e);
	}
}

void Window::focus()
{
	//Restore window if needed
	if (!m_Shown)
	{
		SDL_ShowWindow(m_Window);
	}

	//Move window forward
	SDL_RaiseWindow(m_Window);
}
void Window::Update(float deltatime)
{
	if (!m_Minimized)
	{
		//update scene
		if (m_SceneList.size() > 0)
			m_SceneList.at(m_CurrentScene)->RootUpdate(deltatime);
	}
}

void Window::Draw()
{
	if (!m_Minimized)
	{
		//draw scene
		if (m_SceneList.size() > 0)
			m_SceneList.at(m_CurrentScene)->RootDraw();

		//Update screen
		SDL_RenderPresent(m_Renderer);
	}
}

void Window::AddScene(BaseScene *newscene)
{
	newscene->SetWindow(this);

	if (newscene->RootInitialize())
	{
		m_SceneList.push_back(newscene);
	}
	else
	{
		SafeDelete(newscene);
	}
}

void Window::SetCurrentScene(int scene)
{
	m_SceneList.at(m_CurrentScene)->OnPaused();
	m_CurrentScene = scene%m_SceneList.size();
}