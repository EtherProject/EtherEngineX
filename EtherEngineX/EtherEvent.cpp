#include "EtherEvent.h"

ModuleEvent& ModuleEvent::Instance()
{
	static ModuleEvent* _instance = new ModuleEvent();
	return *_instance;
}

EtherListenerManager& EtherListenerManager::Instance()
{
	static EtherListenerManager* _instance = new EtherListenerManager();
	return *_instance;
}

MouseListener::MouseListener()
{
	type = EVENTTYPE::MOUSE;
}

KeyboardListener::KeyboardListener()
{
	type = EVENTTYPE::KEYBOARD;
}

ModuleEvent::ModuleEvent()
{
	_vCMethods =
	{

	};

	_vMacros =
	{

	};

	_vMetaData =
	{

	};
}

