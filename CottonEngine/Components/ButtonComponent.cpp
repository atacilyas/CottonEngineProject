#include "ButtonComponent.h"

ButtonComponent::ButtonComponent()
	:BaseComponent()
	, m_pNormal	  (nullptr)
	, m_pPressed  (nullptr)
	, m_pInActive (nullptr)
	, m_pHover	  (nullptr)
	, m_pActiveTexture (nullptr)
{
	m_Type = typeid(this).name();
}

ButtonComponent::ButtonComponent(ButtonComponent& other)
	:BaseComponent()
	, m_pNormal(nullptr)
	, m_pPressed(nullptr)
	, m_pInActive(nullptr)
	, m_pHover(nullptr)
	, m_pActiveTexture(nullptr)
{
	m_pNormal = new TextureComponent(*other.m_pNormal);
	m_pPressed = other.m_pPressed;
	m_pInActive = other.m_pInActive;
	m_pHover = other.m_pHover;
	m_pActiveTexture = other.m_pActiveTexture;
	m_State = other.m_State;
	m_Bounds = other.m_Bounds;
	m_ClickEvent = other.m_ClickEvent;
}



ButtonComponent::~ButtonComponent()
{
	if (m_State != ButtonState::Normal)
		SafeDelete(m_pNormal);
	if (m_State != ButtonState::Hover)
		SafeDelete(m_pHover);
	if (m_State != ButtonState::InActive)
		SafeDelete(m_pInActive);
	if (m_State != ButtonState::Pressed)
		SafeDelete(m_pPressed);
}

void ButtonComponent::BackgroundDraw()
{
}

bool ButtonComponent::BackgroundInitialize()
{
	SetState(m_State);
	return true;
}
void ButtonComponent::BackgroundUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}
void ButtonComponent::BackgroundEvent(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);

	if (true)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (   x > m_pTransformComponent->GetPosition().x - (m_Bounds.w / 2.0f)
			&& x < m_pTransformComponent->GetPosition().x + (m_Bounds.w / 2.0f)
			&& y > m_pTransformComponent->GetPosition().y - (m_Bounds.h / 2.0f)
			&& y < m_pTransformComponent->GetPosition().y + (m_Bounds.h / 2.0f))
		{
			if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN)
			{
				SetState(Pressed);
			}
			else if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP)
			{
				SetState(Hover);
				m_ClickEvent();
			}
			else if(m_State != Pressed)
			{
				SetState(Hover);
			}
		}
		else
		{
			SetState(Normal);
		}
	}
}

void ButtonComponent::AddTexture(TextureComponent* texture, ButtonState type)
{
	texture->SetScene(GetScene());
	switch (type)
	{
	case ButtonComponent::Normal:
		m_pNormal = texture;
		break;
	case ButtonComponent::Pressed:
		m_pPressed = texture;
		break;
	case ButtonComponent::InActive:
		m_pInActive = texture;
		break;
	case ButtonComponent::Hover:
		m_pHover = texture;
		break;
	default:
		break;
	}
}

void ButtonComponent::SetBounds(SDL_Rect rect)
{
	m_Bounds.x = rect.x;
	m_Bounds.y = rect.y;
	m_Bounds.w = rect.w;
	m_Bounds.h = rect.h;
}

void ButtonComponent::SetBounds(int x,int y,int w,int h)
{
	m_Bounds.x = x;
	m_Bounds.y = y;
	m_Bounds.w = w;
	m_Bounds.h = h;
}

void ButtonComponent::SetState(ButtonState state)
{
	switch (m_State)
	{
	case ButtonComponent::Normal:
		if(HasChild(m_pNormal))
			RemoveChild(m_pNormal);
		break;
	case ButtonComponent::Pressed:
		if (HasChild(m_pPressed))
			RemoveChild(m_pPressed);
		break;
	case ButtonComponent::InActive:
		if (HasChild(m_pInActive))
			RemoveChild(m_pInActive);
		break;
	case ButtonComponent::Hover:
		if (HasChild(m_pHover))
			RemoveChild(m_pHover);
		break;
	default:
		break;
	}

	m_State = state;

	switch (state)
	{
	case ButtonComponent::Normal:
		if (m_pNormal != nullptr)
		{
			AddChild(m_pNormal);
			m_pActiveTexture = m_pNormal;
		}
		break;
	case ButtonComponent::Pressed:
		if (m_pPressed != nullptr)
		{
			AddChild(m_pPressed);
			m_pActiveTexture = m_pPressed;
		}
		break;
	case ButtonComponent::InActive:
		if (m_pInActive != nullptr)
		{
			AddChild(m_pInActive); 
			m_pActiveTexture = m_pInActive;
		}
		break;
	case ButtonComponent::Hover:
		if (m_pHover != nullptr)
		{
			AddChild(m_pHover);
			m_pActiveTexture = m_pHover;
		}
		break;
	default:
		break;
	}
}

void ButtonComponent::SetClickEvent(function<void()> clickevent)
{
	m_ClickEvent = clickevent;
}
