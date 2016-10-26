#include "BaseComponent.h"
#include "../stdafx.h"
#include <algorithm>

BaseComponent::BaseComponent()
{
	//m_Type = typeid(this).name();
	m_pParent = nullptr;
	m_pTransformComponent = new TransformComponent();
	m_pScene = nullptr;
	m_RenderDepth = 0;
}


BaseComponent::~BaseComponent()
{
	SafeDelete<TransformComponent>(m_pTransformComponent);
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		SafeDelete<BaseComponent>(m_pChildren.at(i));
	}
}

void BaseComponent::AddChild(BaseComponent* child)
{
	if (!HasChild(child))
	{
		m_pChildren.push_back(child);
		child->SetWindow(m_pWindow);
		child->setParent(this);
		child->SetScene(m_pScene);
		child->Initialize();
	}
}

bool BaseComponent::HasChild(BaseComponent* child)
{
	return find(m_pChildren.begin(), m_pChildren.end(), child) != m_pChildren.end();
}


void BaseComponent::RemoveChild(BaseComponent* child, bool destroy)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), child);
	if (destroy)
	{
		SafeDelete<BaseComponent>(child);
	}
	it = m_pChildren.erase(it);
}

void BaseComponent::setParent(BaseComponent *parent)
{
	m_pParent = parent;
	GetTransform()->SetParent(parent->GetTransform());
	SetScene(parent->GetScene());
}

void BaseComponent::Draw()
{
	GetTransform()->UpdateTransforms(1);
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren.at(i)->Draw();
	}

	BackgroundDraw();
}

void BaseComponent::SetScene(BaseScene* scene)
{
	m_pScene = scene;
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren.at(i)->SetScene(scene);
		m_pChildren.at(i)->SetWindow(scene->GetWindow());
	}
}

bool BaseComponent::Initialize()
{
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren.at(i)->BackgroundInitialize();
	}
	return BackgroundInitialize();
}

bool SortBaseComponents(BaseComponent* one, BaseComponent* two)
{
	return one->GetRenderDepth() > two->GetRenderDepth();
}

void BaseComponent::Update(float deltatime)
{
	sort(m_pChildren.begin(), m_pChildren.end(), SortBaseComponents);
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren.at(i)->BackgroundUpdate(deltatime);
	}
	BackgroundUpdate(deltatime);
}

void BaseComponent::Event(SDL_Event e)
{
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren.at(i)->BackgroundEvent(e);
	}
	BackgroundEvent(e);
}