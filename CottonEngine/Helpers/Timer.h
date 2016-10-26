#pragma once

class Timer
{
private:
	//The ticks stored when the timer was paused
	int Ticks;
	int GameStartTime;
	int pauseTime;
	int hasBeenPausedFor;

	bool IsActive;

public:
	//Initializes variables
	Timer();

	//The various clock actions
	void Start();
	void Stop();
	void Pause(bool pause = true);

	//Gets the timer's time
	int GetTicks();
	bool GetIsActive();
};

