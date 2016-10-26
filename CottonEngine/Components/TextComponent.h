#pragma once
#include "BaseComponent.h"

class TextComponent : public BaseComponent
{
public:
	TextComponent();
	~TextComponent();

	bool BackgroundInitialize();
	const bool SetText(const string text,const SDL_Color color);
	bool LoadFont(string path,int size);
	void SetFont(TTF_Font *font);

	void BackgroundUpdate(float deltatime);
	void BackgroundEvent(SDL_Event e);
//	void BackgroundOnTrigger(b2Contact* contact, bool begin = true);

private:
	void BackgroundDraw();

	TTF_Font* m_pFont;
	SDL_Texture* m_Texture;
	SDL_Renderer* m_pRenderer;
	DOUBLE2 m_ImageSize;
};
