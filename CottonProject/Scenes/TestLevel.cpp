#include "TestLevel.h"
#include "../../CottonEngine/stdafx.h"

#include <string>
TestLevel::TestLevel()
	:BaseScene()
{
}


TestLevel::~TestLevel()
{
}

bool TestLevel::Initialize()
{
	cout << "initialize scene" << endl;

	auto cam = new CameraComponent();
	AddChild(cam);
	cam->SetActive();
	m_BackgroundColor = { 97,171,90, 255 };
	
	//LuaManager::GetInstance()->SetScene(this);
	//auto k = LuaManager::GetInstance();
	return true;
}
void TestLevel::Update(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

void TestLevel::Draw()
{
}

void TestLevel::Event(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);
	if (true)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			GetCamera()->GetTransform()->Move(-4, 0);
			break;
		case SDLK_w:
			GetCamera()->GetTransform()->Move(0, -4);
			break;
		case SDLK_s:
			GetCamera()->GetTransform()->Move(0, 4);
			break;
		case SDLK_d:
			GetCamera()->GetTransform()->Move(4,0);
			break;
		default:
			break;
		}
	}
}

void TestLevel::OnPaused()
{

}