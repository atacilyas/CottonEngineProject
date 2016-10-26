#include "TextureComponent.h"
#include "../BaseScene.h"
#include "../Components/CameraComponent.h"

TextureComponent::TextureComponent()
	:BaseComponent()
	,m_Flip(SDL_FLIP_NONE)
	,m_IsActive(true)
{
	m_Type = typeid(this).name();
}

TextureComponent::~TextureComponent()
{
	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}
}

bool TextureComponent::BackgroundInitialize()
{
	return true;
}

bool TextureComponent::LoadTexture(string path)
{
	if (m_pWindow == nullptr)
	{
		m_pWindow = GetScene()->GetWindow();
	}

	//load image on to surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "TextureComponent::Initialize loading image failed" << endl;
		return false;
	}

	//convert surface to texture (texture drawing is done on the gpu)
	m_pRenderer = m_pWindow->GetRenderer();
	m_Texture = SDL_CreateTextureFromSurface(m_pRenderer, loadedSurface);

	//get image size
	m_ImageSize = DOUBLE2(loadedSurface->w, loadedSurface->h);
	m_ClippingRect.x = 0;
	m_ClippingRect.y = 0;
	m_ClippingRect.w = (int)m_ImageSize.x;
	m_ClippingRect.h = (int)m_ImageSize.y;

	//free surface
	SDL_FreeSurface(loadedSurface);

	return true;
}


bool TextureComponent::LoadTexture(SDL_Surface* surface)
{
	if (m_pWindow == nullptr)
	{
		m_pWindow = GetScene()->GetWindow();
	}

	//load image on to surface
	SDL_Surface* loadedSurface = surface;
	if (loadedSurface == NULL)
	{
		cout << "TextureComponent::Initialize loading image failed" << endl;
		return false;
	}

	//convert surface to texture (texture drawing is done on the gpu)
	m_pRenderer = m_pWindow->GetRenderer();
	SDL_DestroyTexture(m_Texture);
	m_Texture = SDL_CreateTextureFromSurface(m_pRenderer, loadedSurface);
	if (m_Texture == nullptr)
	{
		cout << "TextureComponent::LoadTexture loading image failed" << endl;
	}
	//get image size
	m_ImageSize = DOUBLE2(loadedSurface->w, loadedSurface->h);
	m_ClippingRect.x = 0;
	m_ClippingRect.y = 0;
	m_ClippingRect.w = (int)m_ImageSize.x;
	m_ClippingRect.h = (int)m_ImageSize.y;
	//free surface
	//SDL_FreeSurface(loadedSurface);

	return true;
}

bool TextureComponent::LoadTexture(TextureComponent* texture)
{
	if (m_pWindow == nullptr)
	{
		m_pWindow = GetScene()->GetWindow();
	}

	m_Texture = texture->m_Texture;
	m_pRenderer = texture->m_pRenderer;
	m_ImageSize = texture->m_ImageSize;
	m_ClippingRect = texture->m_ClippingRect;
	m_Flip = texture->m_Flip;
	return true;
}

void TextureComponent::BackgroundUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

DOUBLE2 TextureComponent::GetSize()
{
	return DOUBLE2(m_ClippingRect.w * GetTransform()->GetScale().x, m_ClippingRect.h * GetTransform()->GetScale().y);
}

void TextureComponent::BackgroundDraw()
{
	if (m_IsActive)
	{
		//get transforms
		double 	angle = (double)GetTransform()->GetWorldRotation();
		DOUBLE2	position = GetTransform()->GetWorldPosition();
		DOUBLE2	scale = GetTransform()->GetWorldScale();

		//move depending on camera position
		auto cc = GetScene()->GetCamera()->GetTransform()->GetPosition();
		position.x -= cc.x;
		position.y -= cc.y;

		//picture size depending on cliprect and scale
		SDL_Rect dstrect;
		dstrect.x = (int)(position.x - (m_ClippingRect.w * scale.x) / 2.0f);
		dstrect.y = (int)(position.y - (m_ClippingRect.h * scale.y) / 2.0f);
		dstrect.w = (int)(m_ClippingRect.w * scale.x);
		dstrect.h = (int)(m_ClippingRect.h * scale.y);

		//rotation center
		SDL_Point center;
		center.x = (int)((m_ClippingRect.w / 2) * scale.x);
		center.y = (int)((m_ClippingRect.h / 2) * scale.y);

		SDL_RenderCopyEx(m_pRenderer, m_Texture, &m_ClippingRect, &dstrect, angle, &center, m_Flip);
	}
}

void TextureComponent::BackgroundEvent(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);
}

void TextureComponent::Flip(SDL_RendererFlip flip)
{
	m_Flip = flip;
}

void TextureComponent::SetActive(bool active)
{
	m_IsActive = active;
}