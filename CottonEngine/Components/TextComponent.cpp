#include "TextComponent.h"
#include "../BaseScene.h"
#include "../Components/CameraComponent.h"
TextComponent::TextComponent()
	:BaseComponent()
	,m_pFont(nullptr)
{
	m_Type = typeid(this).name();
}


TextComponent::~TextComponent()
{
	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}
}
bool TextComponent::BackgroundInitialize()
{
	return true;
}

bool TextComponent::LoadFont(string path, int size)
{
	m_pFont = TTF_OpenFont(path.c_str(), size);
	if (m_pFont == nullptr)
	{
		return false;
	}
	return true;
}

const bool TextComponent::SetText(const string text,const SDL_Color color)
{
	//check if we have a working font to draw
	if (m_pFont == nullptr)
	{
		cout << "TextComponent::Create font not found" << endl;
		return false;
	}

	//load text on to surface
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(m_pFont, text.c_str(), color);
	if (loadedSurface == NULL)
	{
		const char * a = TTF_GetError();
		cout << "TextComponent::Create creating text failed //" << a << endl;
		return false;
	}

	//convert surface to texture (texture drawing is done on the gpu)
	m_pRenderer = m_pWindow->GetRenderer();
	
	//clear previous text
	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}
	m_Texture = SDL_CreateTextureFromSurface(m_pRenderer, loadedSurface);
	if (m_Texture == nullptr)
	{
		const char* t = SDL_GetError();
		cout << "TextComponent::Create creating texture failed //" << t << endl;
		return false;
	}
	//get image size
	m_ImageSize = DOUBLE2((double)loadedSurface->w, (double)loadedSurface->h);
	//clear surface
	SDL_FreeSurface(loadedSurface);
	
	return true;
}

void TextComponent::SetFont(TTF_Font *font)
{
	m_pFont = font;
}

void TextComponent::BackgroundUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

void TextComponent::BackgroundDraw()
{
	//get transforms
	double 	angle = (double)GetTransform()->GetWorldRotation();
	DOUBLE2	position = GetTransform()->GetWorldPosition();
	DOUBLE2	scale = GetTransform()->GetWorldScale();

	//move depending on camera position
	
	position.x -= GetScene()->GetCamera()->GetTransform()->GetPosition().x;
	position.y -= GetScene()->GetCamera()->GetTransform()->GetPosition().y;

	SDL_Rect dstrect;
	dstrect.x = (int)(position.x - (m_ImageSize.x * scale.x) / 2.0f);
	dstrect.y = (int)(position.y - (m_ImageSize.y * scale.y) / 2.0f);
	dstrect.w = (int)(m_ImageSize.x * scale.x);
	dstrect.h = (int)(m_ImageSize.y * scale.y);

	SDL_Point center;
	center.x = (int)((m_ImageSize.x / 2) * scale.x);
	center.y = (int)((m_ImageSize.y / 2) * scale.y);

	//null is sourcerect
	SDL_RenderCopyEx(m_pRenderer, m_Texture, nullptr, &dstrect, angle, &center, SDL_FLIP_NONE);
}

void TextComponent::BackgroundEvent(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);
}

/*void TextComponent::BackgroundOnTrigger(b2Contact* contact, bool begin)
{
	UNREFERENCED_PARAMETER(begin);
	UNREFERENCED_PARAMETER(contact);
}*/