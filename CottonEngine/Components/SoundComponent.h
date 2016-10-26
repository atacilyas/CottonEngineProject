#pragma once
#include "BaseComponent.h"
#include <vector>
class SoundComponent :
	public BaseComponent
{
public:
	SoundComponent();
	~SoundComponent();

	bool BackgroundInitialize();
	void BackgroundUpdate(float deltatime);
	void BackgroundEvent(SDL_Event e);
//	void BackgroundOnTrigger(b2Contact* contact, bool begin = true);

	//loading
	bool LoadSound(string path);
	bool LoadMusic(string path);
	
	//basic sound operations 
	void Play();	//beware you con only play one music at the same time
	void Pause();
	void Stop();

	void Loop(int amount = -1);
	void SetChannel(int channel);
	
	//sound groups
	void SetGroup(int group);
	int GetGroup(){ return m_ChannelGroup; };

	static void PlayGroup(int group);
	static void PauseGroup(int group);
	static void StopGroup(int group);

private:
	void BackgroundDraw();
	Mix_Chunk *m_pSoundEffect;
	Mix_Music *m_pMusic;
	int
		m_LoopAmount,
		m_Channel,
		m_ChannelGroup,
		m_GroupElement;

	bool m_IsPaused;

	static vector<vector<int>>m_ChannelGroups;
};

