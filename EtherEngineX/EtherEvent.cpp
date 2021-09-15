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

}

KeyboardListener::KeyboardListener()
{

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

	_vMacros =
	{

	};

	_vMetaData =
	{
		{
			"EtherListener",
			nullptr,
			{
				{"SetButtonDown", event_SetButtonDown},
				{"SetButtonUp", event_SetButtonUp},
				{"SetMotion", event_SetMotion},
				{"SetWheel", event_SetWheel},

				{"GetCursorPoint", event_GetCursorPoint},
				{"GetWheelLength", event_GetWheelLength}
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
		lua_rawgeti(L, LUA_REGISTRYINDEX, callDown);
		break;
	case SDL_MOUSEBUTTONUP:
		lua_rawgeti(L, LUA_REGISTRYINDEX, callUp);
		break;
	case SDL_MOUSEMOTION:
		lua_rawgeti(L, LUA_REGISTRYINDEX, callMotion);
		break;
	case SDL_MOUSEWHEEL:
		lua_rawgeti(L, LUA_REGISTRYINDEX, callWheel);
		break;
	}
}

void KeyboardListener::callBack(lua_State* L, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		lua_rawgeti(L, LUA_REGISTRYINDEX, callDown);
		break;
	case SDL_KEYUP:
		lua_rawgeti(L, LUA_REGISTRYINDEX, callUp);
		break;
	}
}

ETHER_API CreateMouseListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	LISTENER_TYPE type = LISTENER_TYPE::MOUSE;
	EtherListener* pListener = new EtherListener(name, type);

	EtherListener** uppListener = (EtherListener**)lua_newuserdata(L, sizeof(EtherListener*));
	*uppListener = pListener;
	luaL_getmetatable(L, "EtherListener");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API CreateKeyboardListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	LISTENER_TYPE type = LISTENER_TYPE::KEYBOARD;
	EtherListener* pListener = new EtherListener(name, type);

	EtherListener** uppListener = (EtherListener**)lua_newuserdata(L, sizeof(EtherListener*));
	*uppListener = pListener;
	luaL_getmetatable(L, "EtherListener");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API event_SetButtonDown(lua_State* L)
{

}

ETHER_API event_SetButtonUp(lua_State* L)
{

}

ETHER_API event_SetMotion(lua_State* L)
{

}

ETHER_API event_SetWheel(lua_State* L)
{

}

ETHER_API event_GetCursorPoint(lua_State* L)
{
	
}

ETHER_API event_GetWheelLength(lua_State* L)
{
	
}

ETHER_API __gc_Listener(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));
	delete pListener;

	return 0;
}