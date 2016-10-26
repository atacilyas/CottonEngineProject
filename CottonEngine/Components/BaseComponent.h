#pragma once
#include "TransformComponent.h"
#include <vector>
#include "../BaseScene.h"
class BaseScene;
class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	void Draw();
	bool Initialize();
	void Update(float deltatime);
	void Event(SDL_Event e);

	void SetRenderDepth(int depth){ m_RenderDepth = depth; }
	int GetRenderDepth(){ return m_RenderDepth; }
	void SetScene(BaseScene* scene);
	BaseScene * GetScene() { return m_pScene; }
	void SetWindow(Window* window){	m_pWindow = window; }
	Window* GetWindow() { return m_pWindow; }
	void AddChild(BaseComponent* child);
	bool HasChild(BaseComponent* child);
	void RemoveChild(BaseComponent* child,bool destroy = false);
	BaseComponent * GetParent(){ return m_pParent; }
	string GetType() { return m_Type; }
	TransformComponent* GetTransform(){ return m_pTransformComponent; }
protected:
	virtual void BackgroundDraw() = 0;
	virtual bool BackgroundInitialize() = 0;
	virtual void BackgroundUpdate(float deltatime) = 0;
	virtual void BackgroundEvent(SDL_Event e) = 0;

	TransformComponent *m_pTransformComponent;
	vector<BaseComponent *>m_pChildren;
	Window* m_pWindow;

	string m_Type;
private:
	void setParent(BaseComponent *parent);
	BaseComponent *m_pParent;
	BaseScene* m_pScene;
	int m_RenderDepth;
};

