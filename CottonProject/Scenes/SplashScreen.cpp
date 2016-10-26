#include "SplashScreen.h"
#include "../../CottonEngine/stdafx.h"
#include <string>

#define TO_STREAM(stream,variable) (stream) <<#variable << endl;

SplashScreen::SplashScreen()
	:BaseScene()
{
}


SplashScreen::~SplashScreen()
{
}

bool SplashScreen::Initialize()
{
	cout << "initialize scene" << endl;

	auto cam = new CameraComponent();
	AddChild(cam);
	cam->SetActive();
	m_BackgroundColor = { 86,52,41,255 };

	m_pText = new TextComponent();
	SDL_Color color = { 79,0,0, 1 };
	m_pText->LoadFont("Rescources/Fonts/ELEPHNT.ttf", 40);
	m_pText->GetTransform()->Translate(GetWindow()->GetSize() / 2.0f);
	AddChild(m_pText);
	m_pText->SetText("ilyas ataç", color);
	m_pText->SetRenderDepth(0);

	
	time.Start();
	pausetimer.Stop();
	return true;
}
void SplashScreen::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	m_pText->GetTransform()->Translate(GetWindow()->GetSize() / 2.0f);
	m_pText->GetTransform()->Scale(GetWindow()->GetSize() / 180.0f);
	SDL_Color color = { 169,199,126, 1 };
	m_pText->SetText(to_string((time.GetTicks()/1000)+1), color);

	if ((time.GetTicks() / 1000) >= 5)
	{
		time.Stop();
		m_pWindow->SetCurrentScene(1);
	}
	else if (time.GetTicks() == 0)
	{
		time.Start();
	}
}

void SplashScreen::Draw()
{
}

void SplashScreen::OnPaused()
{
}

void SplashScreen::Event(SDL_Event e)
{
	if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_F1:
			cout << "f1" << endl;
			time.Pause();
			break;
		case SDLK_F2:
			cout << "f2" << endl;
			time.Pause(false);
			break;
		default:
			break;
		}
	}
}