#include "Timer.h"
#include "../stdafx.h"

Timer::Timer()
	: IsActive(false)
	, GameStartTime(0)
	, Ticks(0)
	, pauseTime(0)
	, hasBeenPausedFor(0)
{
}

//The various clock actions
void Timer::Start()
{
	IsActive = true;
	GameStartTime = SDL_GetTicks();
	Ticks = 0;
	pauseTime = 0;
	hasBeenPausedFor = 0;
}
void Timer::Stop()
{
	IsActive = false;
	GameStartTime = 0;
	Ticks = 0;
	pauseTime = 0;
	hasBeenPausedFor = 0;
}

void Timer::Pause(bool pause)
{
	if (pause)
	{
		pauseTime = SDL_GetTicks();
		IsActive = false;
	}
	else if(!IsActive)
	{
		IsActive = true;
		GameStartTime -= SDL_GetTicks() - pauseTime;
	}
}

//Gets the timer's time
int Timer::GetTicks()
{
	if (IsActive)
	{
		//cout << "pausetime " << pauseTime << endl;
		Ticks = SDL_GetTicks() - GameStartTime;
	}
	return Ticks;
}

bool Timer::GetIsActive()
{
	return IsActive;
}