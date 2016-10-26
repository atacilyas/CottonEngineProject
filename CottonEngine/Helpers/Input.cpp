#include "Input.h"

Input* Input::m_instance = nullptr;

Input* Input::GetInstance()
{
	if (!m_instance)
	{
		Input::m_instance = new Input();
	}

	return m_instance;
}

void Input::destroy()
{
	delete Input::m_instance;
	Input::m_instance = nullptr;
}

bool Input::GetKey(SDL_Keycode key)
{
	if (m_Keys.size() > 0)
	{
		return 	m_Keys[key];
	}
	else
	{
		return false;
	}
};

void Input::SetKeyDown(SDL_Keycode key)
{
	m_Keys[key] = true;
}

void Input::SetKeyUp(SDL_Keycode key)
{
	m_Keys[key] = false;
}