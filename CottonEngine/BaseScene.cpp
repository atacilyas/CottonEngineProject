#include "BaseScene.h"
#include "../Components/BaseComponent.h"
#include "../Components/CameraComponent.h"
#include <algorithm>

BaseScene::BaseScene()
{
	m_pOriginalCamera = new CameraComponent();
	m_pActiveCamera = m_pOriginalCamera;
}


BaseScene::~BaseScene()
{
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		SafeDelete(m_pChildren.at(i));	
	}
	SafeDelete(m_pOriginalCamera);
}

void BaseScene::SetActiveCamera(CameraComponent* child)
{
	m_pActiveCamera = child;
}
CameraComponent* BaseScene::GetCamera()
{
	return m_pActiveCamera; 
}

void BaseScene::AddChild(BaseComponent* child)
{
	m_pChildren.push_back(child);
	child->SetScene(this);
	child->SetWindow(GetWindow());
	child->Initialize();
}

void BaseScene::RemoveChild(BaseComponent* component, bool destroy)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), component);
	if (it != m_pChildren.end())
	{
		if (destroy)
		{
			SafeDelete(*it);
		}
		m_pChildren.erase(it);
	}
}

bool BaseScene::RootInitialize()
{
	bool succes = true;

	if (!Initialize())
		succes = false;
	//for each (BaseComponent* child in m_pChildren)
	//{
	//	if (!child->Initialize())
	//		succes = false;
	//}
	return succes;
}

bool SortComponents(BaseComponent* one, BaseComponent* two)
{
	return one->GetRenderDepth() > two->GetRenderDepth();
}

void BaseScene::RootUpdate(float deltatime)
{
	if (m_pActiveCamera == nullptr)
	{
		m_pActiveCamera = m_pOriginalCamera;
	}
	Update(deltatime);
	sort(m_pChildren.begin(), m_pChildren.end(), SortComponents);
	for each (BaseComponent* child in m_pChildren)
	{
		child->Update(deltatime);
	}
}

void BaseScene::RootDraw()
{
	SDL_Color color = m_BackgroundColor;
	SDL_SetRenderDrawColor(GetWindow()->GetRenderer(), (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.b);
	SDL_RenderClear(GetWindow()->GetRenderer());

	Draw();
	for each (BaseComponent* child in m_pChildren)
	{
		child->Draw();
	}
}

void BaseScene::RootEvent(SDL_Event e)
{
	Event(e);
	for each (BaseComponent* child in m_pChildren)
	{
		child->Event(e);
	}
}

