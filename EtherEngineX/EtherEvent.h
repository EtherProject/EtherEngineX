#ifndef _EVENT_H_
#define _EVENT_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <unordered_map>

enum class LISTENER_TYPE
{
	NONE = 0,
	MOUSE,
	KEYBOARD
};

class MouseListener
{
public:
	MouseListener();
	~MouseListener() {}

	void callBack(lua_State*, SDL_Event*);

	lua_Integer callDown = LUA_REFNIL;
	lua_Integer callUp = LUA_REFNIL;
	lua_Integer callMotion = LUA_REFNIL;
	lua_Integer callWheel = LUA_REFNIL;

	SDL_Point cursorPoint;
	SDL_Point wheelLength;
};

class KeyboardListener
{
public:
	KeyboardListener();
	~KeyboardListener() {}

	void callBack(lua_State*, SDL_Event*);

	lua_Integer callDown = LUA_REFNIL;
	lua_Integer callUp = LUA_REFNIL;
};

class EtherListener
{
public:
	EtherListener(const char*, LISTENER_TYPE);
	~EtherListener() {}

	LISTENER_TYPE type;
	const char* name;

	union
	{
		MouseListener mouse;
		KeyboardListener keyboard;
	};
};

class EtherListenerManager
{
public:
	static EtherListenerManager& Instance();

	~EtherListenerManager() {}

	SDL_Event event;

	LISTENER_TYPE currentType = LISTENER_TYPE::NONE;

	std::unordered_map<const char*, EtherListener*> mapListener;
private:
	EtherListenerManager() {}
};

class ModuleEvent : public EtherModule
{
public:
	static ModuleEvent& Instance();
	~ModuleEvent() {}
private:
	ModuleEvent();
};

ETHER_API CreateMouseListener(lua_State* L);

ETHER_API CreateKeyboardListener(lua_State* L);

ETHER_API event_SetButtonDown(lua_State* L);

ETHER_API event_SetButtonUp(lua_State* L);

ETHER_API event_SetMotion(lua_State* L);

ETHER_API event_SetWheel(lua_State* L);

ETHER_API event_GetCursorPoint(lua_State* L);

ETHER_API event_GetWheelLength(lua_State* L);

ETHER_API __gc_Listener(lua_State* L);

#endif // !_EVENT_H_