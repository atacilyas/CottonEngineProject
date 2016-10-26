#pragma once
#include "stdafx.h"
class BaseComponent;
class CameraComponent;
#include <vector>
#include "Window.h"

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	//background rendering and updating
	bool RootInitialize();
	void RootUpdate(float deltatime);
	void RootDraw();
	void RootEvent(SDL_Event e);

	//camera
	CameraComponent* GetCamera();
	void SetActiveCamera(CameraComponent*);

	//window
	void SetWindow(Window * window){ m_pWindow = window; }
	Window * GetWindow(){ return m_pWindow; }

	//on scene paused
	virtual void OnPaused() {};

	//children
	void AddChild(BaseComponent* component);
	template<class T>
	T* GetChild()
	{
		vector<T*> found;
		for each (BaseComponent* child in m_pChildren)
		{
			if (typeid(T*).name() == child->GetType())
			{
				found.push_back((T*)child);
			}
		}
		if (found.size() > 0)
		{
			return found.at(0);
		}
		else
		{
			return nullptr;
		}
	}
	void RemoveChild(BaseComponent* component, bool destroy = false);

protected:
	//rendering and updating
	virtual bool Initialize() = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Draw(){};
	virtual void Event(SDL_Event e) = 0;

	Window * m_pWindow;
	vector<BaseComponent *>m_pChildren;
	SDL_Color m_BackgroundColor;
private:
	CameraComponent* m_pActiveCamera,*m_pOriginalCamera;
};

template<class T>
void SafeDelete(T*& object)
{
	if (object)
	{
		if (object != nullptr)
		{
			delete object;
			object = nullptr;
		}
	}
}
