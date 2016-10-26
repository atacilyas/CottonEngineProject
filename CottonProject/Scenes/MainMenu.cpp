#include "MainMenu.h"
#include "../../CottonEngine/stdafx.h"
#include <string>
MainMenu::MainMenu()
	:BaseScene()
{
}


MainMenu::~MainMenu()
{
}

bool MainMenu::Initialize()
{
	cout << "initialize scene" << endl;
	m_BackgroundColor = { 97,171,90, 255 };

	//create components
	auto normal = new TextureComponent();
	auto hover = new TextureComponent();
	auto pressed = new	 TextureComponent();
	auto inactive = new TextureComponent();
	m_pButton = new ButtonComponent();
	//add to scene
	AddChild(m_pButton);
	m_pButton->AddTexture(normal, (ButtonComponent::ButtonState::Normal));
	m_pButton->AddTexture(pressed, (ButtonComponent::ButtonState::Pressed));
	m_pButton->AddTexture(hover, (ButtonComponent::ButtonState::Hover));
	m_pButton->AddTexture(inactive, (ButtonComponent::ButtonState::InActive));

	//set values
	m_pButton->SetBounds(0,0,92,70);
	m_pButton->SetState(ButtonComponent::ButtonState::Normal);
	m_pButton->SetClickEvent([&]() 
	{
		m_pWindow->SetCurrentScene(0); cout << "click" << endl; 
	});

	//load files
	if (!normal->LoadTexture("Rescources/Sprites/PNG/HUD/hudJewel_blue.png"))
		return false;
	if (!hover->LoadTexture("Rescources/Sprites/PNG/HUD/hudJewel_green.png"))
		return false;
	if (!pressed->LoadTexture("Rescources/Sprites/PNG/HUD/hudJewel_red.png"))
		return false;
	if (!inactive->LoadTexture("Rescources/Sprites/PNG/HUD/hudJewel_yellow.png"))
		return false;

	return true;
}
void MainMenu::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	m_pButton->GetTransform()->Translate(m_pWindow->GetSize() /2.0f);
}

void MainMenu::Draw()
{
}



void MainMenu::Event(SDL_Event e)
{
	//check for keypresses
	UNREFERENCED_PARAMETER(e);
	if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_F1:
			cout << "f1" << endl;
			m_pButton->SetState((ButtonComponent::ButtonState::Hover));
			break;
		case SDLK_F2:
			cout << "f2" << endl;
			m_pButton->SetState((ButtonComponent::ButtonState::InActive));
			break;
		case SDLK_F3:
			cout << "f3" << endl;
			m_pButton->SetState((ButtonComponent::ButtonState::Normal));
			break;
		case SDLK_F4:
			cout << "f4" << endl;
			m_pButton->SetState((ButtonComponent::ButtonState::Pressed));
			break;
		default:
			break;
		}
	}
}

void MainMenu::OnPaused()
{

}