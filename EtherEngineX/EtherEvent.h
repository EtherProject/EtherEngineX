#ifndef _EVENT_H_
#define _EVENT_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <unordered_map>

enum class EVENT_TYPE
{
	NONE = 0,
	MOUSE,
	KEYBOARD,
};

class MouseListener
{
public:
	void Callback(lua_State*, SDL_Event*);

	lua_Integer callDown = LUA_REFNIL;
	lua_Integer callUp = LUA_REFNIL;
	lua_Integer callMotion = LUA_REFNIL;

	SDL_Point cursorPoint = { 0,0 };
	SDL_Point wheelLength = { 0,0 };
};

class KeyboardListener
{
public:
	void Callback(lua_State*, SDL_Event*);

	lua_Integer callDown = LUA_REFNIL;
	lua_Integer callUp = LUA_REFNIL;
};

class EtherListener
{
public:
	EtherListener(EVENT_TYPE);

	EVENT_TYPE type;

	MouseListener mouse;
	KeyboardListener keyboard;
};

class EtherListenerManager
{
public:
	EtherListenerManager() {}

	~EtherListenerManager() {}

	SDL_Event event;
	EVENT_TYPE currentType = EVENT_TYPE::NONE;

	std::unordered_map<const char*, EtherListener*> mapListener;
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

ETHER_API listener_SetButtonDown(lua_State* L);

ETHER_API listener_SetButtonUp(lua_State* L);

ETHER_API listener_SetMotion(lua_State* L);

ETHER_API listener_GetButtonType(lua_State* L);

ETHER_API listener_GetCursorPoint(lua_State* L);

ETHER_API listener_GetWheelLength(lua_State* L);

ETHER_API listener_SetKeyDown(lua_State* L);

ETHER_API listener_SetKeyUp(lua_State* L);

ETHER_API listener_GetKeyType(lua_State* L);

ETHER_API listener_GetKeyMod(lua_State* L);

ETHER_API __gc_Listener(lua_State* L);

#endif // !_EVENT_H_