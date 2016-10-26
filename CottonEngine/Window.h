#pragma once
#include "stdafx.h"
#include <vector>
class BaseScene;

class Window
{
public:
	//Intializes internals
	Window(DOUBLE2 size);
	~Window();

	//Creates window
	bool Initialize();

	//Handles window events
	void handleEvent(SDL_Event& e);

	//Focuses on window
	void focus();

	//Shows windows contents
	void Draw();
	void Update(float deltatime);

	//scenes
	void AddScene(BaseScene *newscene);
	void SetCurrentScene(int scene);

	//Window info
	DOUBLE2 GetSize(){ return m_ScreenSize; }
	SDL_Renderer* GetRenderer(){ return m_Renderer; }
	bool HasMouseFocus() { return m_MouseFocus; }
	bool HasKeyboardFocus() { return m_KeyboardFocus; }
	bool IsMinimized() { return m_Minimized; }
	bool IsShown() { return m_Shown; }
	static int GetAmountOfWindows(){ return m_WindowAmount; };
private:
	//Window data
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	int m_WindowID;

	//Window focus
	bool m_MouseFocus;
	bool m_KeyboardFocus;
	bool m_FullScreen;
	bool m_Minimized;
	bool m_Shown;

	DOUBLE2 m_ScreenSize;

	int m_CurrentScene;
	vector<BaseScene *>m_SceneList;

	static int m_WindowAmount;
};
