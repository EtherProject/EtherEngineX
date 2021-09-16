#include "EtherEvent.h"

#include <iostream>

EtherListenerManager listenerManager;

ModuleEvent& ModuleEvent::Instance()
{
	static ModuleEvent* _instance = new ModuleEvent();
	return *_instance;
}

EtherListener::EtherListener(const char* paramName, LISTENER_TYPE paramType)
{
	name = paramName;
	type = paramType;
}

ModuleEvent::ModuleEvent()
{
	_vCMethods =
	{
		{"CreateMouseListener", CreateMouseListener},
		{"CreateKeyboardListener", CreateKeyboardListener}
	};

	_vMetaData =
	{
		{
			"EtherListener",
			nullptr,
			{
			//Êó±ê¼àÌýÊÂ¼þ
				{"SetButtonDown", listener_SetButtonDown},
				{"SetButtonUp", listener_SetButtonUp},
				{"SetMotion", listener_SetMotion},
				{"SetWheel", listener_SetWheel},

				{"GetButtonState", listener_GetButtonState},
				{"GetCursorPoint", listener_GetCursorPoint},
				{"GetWheelLength", listener_GetWheelLength}
			},
			__gc_Listener
		},
	};
}

void MouseListener::callBack(lua_State* L, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (callDown != LUA_REFNIL)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, callDown);
			lua_pcall(L, 0, 0, 0);
			break;
		}
	case SDL_MOUSEBUTTONUP:
		if (callUp != LUA_REFNIL)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, callUp);
			lua_pcall(L, 0, 0, 0);
			break;
		}
	case SDL_MOUSEMOTION:
		if (callMotion != LUA_REFNIL)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, callMotion);
			lua_pcall(L, 0, 0, 0);
			break;
		}
	case SDL_MOUSEWHEEL:
		if (callWheel != LUA_REFNIL)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, callWheel);
			lua_pcall(L, 0, 0, 0);
			break;
		}
	}
}

void KeyboardListener::callBack(lua_State* L, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		if (callDown != LUA_REFNIL)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, callDown);
			lua_pcall(L, 0, 0, 0);
			break;
		}
	case SDL_KEYUP:
		if (callUp != LUA_REFNIL)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, callUp);
			lua_pcall(L, 0, 0, 0);
			break;
		}
	}
}

ETHER_API CreateMouseListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	EtherListener* pListener = new EtherListener(name, LISTENER_TYPE::MOUSE);
	listenerManager.mapListener[name] = pListener;

	EtherListener** uppListener = (EtherListener**)lua_newuserdata(L, sizeof(EtherListener*));
	*uppListener = pListener;
	luaL_getmetatable(L, "EtherListener");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API CreateKeyboardListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	EtherListener* pListener = new EtherListener(name, LISTENER_TYPE::KEYBOARD);
	listenerManager.mapListener[name] = pListener;

	EtherListener** uppListener = (EtherListener**)lua_newuserdata(L, sizeof(EtherListener*));
	*uppListener = pListener;
	luaL_getmetatable(L, "EtherListener");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API listener_SetButtonDown(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));
	pListener->mouse.callDown = luaL_ref(L, LUA_REGISTRYINDEX);

	return 0;
}

ETHER_API listener_SetButtonUp(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == LISTENER_TYPE::MOUSE)
		pListener->mouse.callUp = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetMotion(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == LISTENER_TYPE::MOUSE)
		pListener->mouse.callMotion = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWheel(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == LISTENER_TYPE::MOUSE)
		pListener->mouse.callWheel = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_GetButtonState(lua_State* L)
{
	lua_pushnumber(L, listenerManager.event.button.button);

	return 1;
}

ETHER_API listener_GetCursorPoint(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "x");
	lua_pushnumber(L, listenerManager.event.motion.x);
	lua_settable(L, -3);

	lua_pushstring(L, "y");
	lua_pushnumber(L, listenerManager.event.motion.y);
	lua_settable(L, -3);

	return 1;
}

ETHER_API listener_GetWheelLength(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "x");
	lua_pushnumber(L, listenerManager.event.wheel.x);
	lua_settable(L, -3);

	lua_pushstring(L, "y");
	lua_pushnumber(L, listenerManager.event.wheel.y);
	lua_settable(L, -3);

	lua_pushstring(L, "direction");
	lua_pushnumber(L, listenerManager.event.wheel.direction);
	lua_settable(L, -3);

	return 1;
}

ETHER_API __gc_Listener(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == LISTENER_TYPE::MOUSE)
	{
		if (pListener->mouse.callDown != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->mouse.callDown);
		else if (pListener->mouse.callUp != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->mouse.callUp);
		else if (pListener->mouse.callMotion != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->mouse.callMotion);
		else if (pListener->mouse.callWheel != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->mouse.callWheel);
	}

	delete pListener;

	return 0;
}