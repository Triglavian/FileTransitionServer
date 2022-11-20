#include "EventHandles.h"

EventHandles* EventHandles::GetInstance()
{
	static EventHandles* instance = new EventHandles();
	//if (instance == nullptr)
	//{
	//	instance = new EventHandles();
	//}
	return instance;
}

void EventHandles::DestroyInstance()
{
	delete EventHandles::GetInstance();
}

bool EventHandles::SetRdyTransEvent()
{
	return SetEvent(rdyTransition);
}

bool EventHandles::WaitRdyTransEvent()
{
	return (WaitForSingleObject(rdyTransition, INFINITE) != WAIT_OBJECT_0);
}

EventHandles::EventHandles()
{
	rdyTransition = CreateEvent(0, 0, 0, 0);
}

EventHandles::~EventHandles()
{
	CloseHandle(rdyTransition);
}
