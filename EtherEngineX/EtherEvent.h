#ifndef _EVENT_H_
#define _EVENT_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <queue>
#include <unordered_map>

class EtherEvent
{
public:

};

class EtherListener
{
public:
	EtherListener();
	~EtherListener();

	Uint32 type;
};

class MouseListener : public EtherListener
{
public:
	MouseListener();
	~MouseListener();

};

class KeyboardListener : public EtherListener
{
public:
	KeyboardListener();
	~KeyboardListener();
};

class EtherListenerManager
{
public:
	static EtherListenerManager& Instance();

	~EtherListenerManager() {}
protected:
	EtherListenerManager() {}

	std::unordered_map<const char*, EtherListener*> listenerMannger;

	std::queue<EtherEvent*> eventQueue;
};

class ModuleEvent : public EtherModule
{
public:
	static ModuleEvent& Instance();
	~ModuleEvent() {}
private:
	ModuleEvent();
};

#endif // !_EVENT_H_