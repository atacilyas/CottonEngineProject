#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <map>

using namespace std;

class Input
{
public:
	static Input* GetInstance();
	static void destroy();

	bool GetKey(SDL_Keycode key);
	void SetKeyDown(SDL_Keycode key);
	void SetKeyUp(SDL_Keycode key);

private:
	map<SDL_Keycode, bool> m_Keys;
	Input(Input const&) {};
	Input& operator=(Input const&) {};
	
protected:
	static Input* m_instance;

	Input() { m_instance = static_cast <Input*> (this); };
	~Input() {  };
};
