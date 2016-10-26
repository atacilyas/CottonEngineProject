#pragma once
#include "BaseComponent.h"


class TextureComponent : public BaseComponent
{
public:
	TextureComponent();
	~TextureComponent();

	bool BackgroundInitialize();
	bool LoadTexture(string path);
	bool LoadTexture(SDL_Surface* surface);
	bool LoadTexture(TextureComponent* texture);

	void BackgroundUpdate(float deltatime);
	void BackgroundEvent(SDL_Event e);
//	void BackgroundOnTrigger(b2Contact* contact, bool begin = true);

	DOUBLE2 GetSize();
	void Flip(SDL_RendererFlip flip);
	void SetClippingRect(SDL_Rect clip){ m_ClippingRect = clip; }
	void SetActive(bool active = true);
	bool GetActive() { return m_IsActive; }

private:
	void BackgroundDraw();
	SDL_Texture* m_Texture;
	SDL_Renderer* m_pRenderer;
	DOUBLE2 m_ImageSize;
	SDL_Rect m_ClippingRect;
	SDL_RendererFlip m_Flip;
	bool m_IsActive;
};
