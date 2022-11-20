#pragma once
#include <Windows.h>

class EventHandles
{
public:
	static EventHandles* GetInstance();
	static void DestroyInstance();
	bool SetRdyTransEvent();
	bool WaitRdyTransEvent();
private:
	EventHandles();
	~EventHandles();
	EventHandles(const EventHandles&) = delete;
	HANDLE rdyTransition;
};

