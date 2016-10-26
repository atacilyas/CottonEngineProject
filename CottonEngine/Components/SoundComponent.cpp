#include "SoundComponent.h"

vector<vector<int>>	SoundComponent::m_ChannelGroups;


SoundComponent::SoundComponent()
	:BaseComponent(),
	m_LoopAmount(0), m_Channel(-1), m_ChannelGroup(-1)
{
	m_Type = typeid(this).name();
	m_pSoundEffect = nullptr;
	m_pMusic = nullptr;
}


SoundComponent::~SoundComponent()
{
	Stop();

	if (m_pSoundEffect != nullptr)
		Mix_FreeChunk(m_pSoundEffect);

	if (m_pMusic != nullptr)
		Mix_FreeMusic(m_pMusic);
}

bool SoundComponent::BackgroundInitialize()
{
	return true;
}

bool SoundComponent::LoadSound(string path)
{
	Stop();

	if (m_pSoundEffect != nullptr)
	{
		Mix_FreeChunk(m_pSoundEffect);
		m_pSoundEffect = nullptr;
	}

	if (m_pMusic != nullptr)
	{
		Mix_FreeMusic(m_pMusic);
		m_pMusic = nullptr;
	}


	m_pSoundEffect = Mix_LoadWAV(path.c_str());
	if (m_pSoundEffect == nullptr)
		cout << "SoundComponent::LoadSound failed to load sound" << endl;
	return m_pSoundEffect != nullptr;
}

bool SoundComponent::LoadMusic(string path)
{
	Stop();

	if (m_pSoundEffect != nullptr)
	{
		Mix_FreeChunk(m_pSoundEffect);
		m_pSoundEffect = nullptr;
	}

	if (m_pMusic != nullptr)
	{
		Mix_FreeMusic(m_pMusic);
		m_pMusic = nullptr;
	}

	m_pMusic = Mix_LoadMUS(path.c_str());
	if (m_pMusic == nullptr)
		cout << "SoundComponent::LoadMusic failed to load music" << endl;

	return m_pMusic != nullptr;
}

void SoundComponent::Play()
{
	if (m_IsPaused)
	{
		if (m_pSoundEffect != nullptr)
		{
			Mix_Resume(m_Channel);
		}
		else if (m_pMusic != nullptr)
		{
			Mix_ResumeMusic();
		}
	}
	else
	{
		if (m_pSoundEffect != nullptr)
		{
			//play sound
			m_Channel = Mix_PlayChannel(m_Channel, m_pSoundEffect, m_LoopAmount);
			m_ChannelGroups.at(m_ChannelGroup).at(m_GroupElement) = m_Channel;
			Mix_GroupChannel(m_Channel, m_ChannelGroup);
		}
		else if (m_pMusic != nullptr)
		{
			//play music
			Mix_PlayMusic(m_pMusic, m_LoopAmount);
			m_Channel = -2;
			m_ChannelGroups.at(m_ChannelGroup).at(m_GroupElement) = -2;
		}
	}
}

void SoundComponent::Pause()
{
	if (m_pSoundEffect != nullptr && Mix_Playing(m_Channel) != 0)
	{
		m_IsPaused = true;
		Mix_Pause(m_Channel);
	}
	else if (m_pMusic != nullptr && Mix_PlayingMusic() != 0)
	{
		m_IsPaused = true;
		Mix_PauseMusic();
	}
}

void SoundComponent::Loop(int amount)
{
	m_LoopAmount = amount;
}

void SoundComponent::SetChannel(int channel)
{
	if (m_pSoundEffect != nullptr)
	{
		m_Channel = channel;
	}
	else
	{
		m_Channel = -2;
	}
	m_ChannelGroups.at(m_ChannelGroup).at(m_GroupElement) = m_Channel;
	
}

void SoundComponent::Stop()
{
	if (m_pSoundEffect != nullptr)
	{
		//play sound
		Mix_HaltChannel(m_Channel);
	}
	else if (m_pMusic != nullptr)
	{
		//play music
		Mix_HaltMusic();
	}
}

void SoundComponent::StopGroup(int group)
{
	auto channelgroup = m_ChannelGroups.at(group);
	for (size_t i = 0; i < channelgroup.size(); i++)
	{
		int id = channelgroup.at(i);
		if (id == -2)
		{
			Mix_HaltMusic();
		}
		else
		{
			Mix_HaltChannel(id);
		}
	}
}

void SoundComponent::SetGroup(int group)
{
	if (m_ChannelGroup == group)
		return;
	if (m_ChannelGroup != -1)
	{
		if (m_ChannelGroups.at(m_ChannelGroup).size() <= 1)
		{
			m_ChannelGroups.erase(m_ChannelGroups.begin() + m_ChannelGroup);
		}
		else
		{
			m_ChannelGroups.at(m_ChannelGroup).erase(m_ChannelGroups.at(m_ChannelGroup).begin() + m_GroupElement);
		}
	}

	m_ChannelGroup = group;
	if (group == (int)m_ChannelGroups.size())
	{
		vector<int> newgroup;
		m_ChannelGroups.push_back(newgroup);
	}
	m_GroupElement = m_ChannelGroups.at(group).size();
	m_ChannelGroups.at(group).push_back(m_Channel);
}

void SoundComponent::PauseGroup(int group)
{
	auto channelgroup = m_ChannelGroups.at(group);
	for (size_t i = 0; i < channelgroup.size(); i++)
	{
		int id = channelgroup.at(i);
		if (id == -2)
		{
			Mix_PauseMusic();
		}
		else
		{
			Mix_Pause(id);
		}
	}
}

void SoundComponent::PlayGroup(int group)
{
	auto channelgroup = m_ChannelGroups.at(group);
	for (size_t i = 0; i < channelgroup.size(); i++)
	{
		int id = channelgroup.at(i);
		if (id == -2)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_Resume(id);
		}
	}
}

void SoundComponent::BackgroundUpdate(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
}

void SoundComponent::BackgroundEvent(SDL_Event e)
{
	UNREFERENCED_PARAMETER(e);
}

void SoundComponent::BackgroundDraw()
{

}

/*void SoundComponent::BackgroundOnTrigger(b2Contact* contact, bool begin)
{
	UNREFERENCED_PARAMETER(begin);
	UNREFERENCED_PARAMETER(contact);
}*/