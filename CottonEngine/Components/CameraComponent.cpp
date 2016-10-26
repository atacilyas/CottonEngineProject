#include "CameraComponent.h"

CameraComponent::CameraComponent()
	:BaseComponent()
{
	m_Type = typeid(this).name();
}


CameraComponent::~CameraComponent()
{
}

bool CameraComponent::BackgroundInitialize()
{
	m_WindowSize = m_pWindow->GetSize();
	return true; 
}

void CameraComponent::BackgroundUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (GetParent() != nullptr)
	{
		DOUBLE2 pos = GetParent()->GetTransform()->GetWorldPosition();
		pos.x -= m_WindowSize.x / 2.0;
		pos.y -= m_WindowSize.y / 2.0;

		GetTransform()->Translate(pos);
	}
}

void CameraComponent::BackgroundEvent(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);
}

void CameraComponent::BackgroundDraw()
{
}


void CameraComponent::SetActive()
{
	if (GetScene() != nullptr)
	{
		GetScene()->SetActiveCamera(this);
	}
	else
	{
		cout << "camera is not a child of a scene" << endl;
	}
}