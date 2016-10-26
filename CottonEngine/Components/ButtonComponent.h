#pragma once
#include "TextureComponent.h"
#include <functional>
class ButtonComponent :	public BaseComponent
{
public:
	ButtonComponent();
	ButtonComponent(ButtonComponent& other);

	~ButtonComponent();

	enum ButtonState
	{
		Normal,
		Pressed,
		InActive,
		Hover
	};

	void AddTexture(TextureComponent* texture, ButtonState type);
	void SetState(ButtonState state);

	void BackgroundDraw();
	bool BackgroundInitialize();
	void BackgroundUpdate(float deltatime);
	void BackgroundEvent(SDL_Event e);
	void SetBounds(SDL_Rect rect);
	void SetBounds(int x, int y, int w, int h);
	void SetClickEvent(function<void()> clickevent);

private:
	TextureComponent* m_pNormal, *m_pPressed, *m_pInActive, *m_pHover, *m_pActiveTexture;
	ButtonState m_State;
	SDL_Rect m_Bounds;
	function<void()> m_ClickEvent;
};

