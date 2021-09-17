#include "EtherEvent.h"

#include <iostream>

EtherListenerManager listenerManager;

ModuleEvent& ModuleEvent::Instance()
{
	static ModuleEvent* _instance = new ModuleEvent();
	return *_instance;
}

EtherListener::EtherListener(EVENT_TYPE paramType)
{
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
		//Êó±êºê
		{"MOUSE_LEFTBUTTON", SDL_BUTTON_LEFT},
		{"MOUSE_RIGHTBUTTON", SDL_BUTTON_RIGHT},
		{"MOUSE_MIDDLEBUTTON", SDL_BUTTON_MIDDLE},

		//¼üÅÌºê
		{"KEY_Q", SDLK_q},
		{"KEY_W", SDLK_w},
		{"KEY_E", SDLK_e},
		{"KEY_R", SDLK_r},
		{"KEY_T", SDLK_t},
		{"KEY_Y", SDLK_y},
		{"KEY_U", SDLK_u},
		{"KEY_I", SDLK_i},
		{"KEY_O", SDLK_o},
		{"KEY_P", SDLK_p},
		{"KEY_A", SDLK_a},
		{"KEY_S", SDLK_s},
		{"KEY_D", SDLK_d},
		{"KEY_F", SDLK_f},
		{"KEY_G", SDLK_g},
		{"KEY_H", SDLK_h},
		{"KEY_J", SDLK_j},
		{"KEY_K", SDLK_k},
		{"KEY_L", SDLK_l},
		{"KEY_Z", SDLK_z},
		{"KEY_X", SDLK_x},
		{"KEY_C", SDLK_c},
		{"KEY_V", SDLK_v},
		{"KEY_B", SDLK_b},
		{"KEY_N", SDLK_n},
		{"KEY_M", SDLK_m},
		{"KEY_0", SDLK_0},
		{"KEY_1", SDLK_1},
		{"KEY_2", SDLK_2},
		{"KEY_3", SDLK_3},
		{"KEY_4", SDLK_4},
		{"KEY_5", SDLK_5},
		{"KEY_6", SDLK_6},
		{"KEY_7", SDLK_7},
		{"KEY_8", SDLK_8},
		{"KEY_9", SDLK_9},
		{"KEY_F1", SDLK_F1},
		{"KEY_F2", SDLK_F2},
		{"KEY_F3", SDLK_F3},
		{"KEY_F4", SDLK_F4},
		{"KEY_F5", SDLK_F5},
		{"KEY_F6", SDLK_F6},
		{"KEY_F7", SDLK_F7},
		{"KEY_F8", SDLK_F8},
		{"KEY_F9", SDLK_F9},
		{"KEY_F10", SDLK_F10},
		{"KEY_F11", SDLK_F11},
		{"KEY_F12", SDLK_F12}
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

				{"GetButtonType", listener_GetButtonType},
				{"GetCursorPoint", listener_GetCursorPoint},
				{"GetWheelLength", listener_GetWheelLength},

			//¼üÅÌ¼àÌýÊÂ¼þ
				{"SetKeyDown", listener_SetKeyDown},
				{"SetKeyUp", listener_SetKeyUp},

				{"GetKeyType", listener_GetKeyType},
				{"GetKeyMod", listener_GetKeyMod}
			},
			__gc_Listener
		},
	};
}

void MouseListener::Callback(lua_State* L, SDL_Event* event)
{
	if (event->button.type == SDL_MOUSEBUTTONDOWN && callDown != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callDown);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->button.type == SDL_MOUSEBUTTONUP && callUp != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callUp);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->motion.type == SDL_MOUSEMOTION && callMotion != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callMotion);
		lua_pcall(L, 0, 0, 0);
	}
}

void KeyboardListener::Callback(lua_State* L, SDL_Event* event)
{
	if (event->key.type == SDL_KEYDOWN && callDown != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callDown);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->key.type == SDL_KEYUP && callUp != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callUp);
		lua_pcall(L, 0, 0, 0);
	}
}

ETHER_API CreateMouseListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	EtherListener* pListener = new EtherListener(EVENT_TYPE::MOUSE);
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

	EtherListener* pListener = new EtherListener(EVENT_TYPE::KEYBOARD);
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

	if (pListener->type == EVENT_TYPE::MOUSE)
		pListener->mouse.callDown = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetButtonUp(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::MOUSE)
		pListener->mouse.callUp = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetMotion(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::MOUSE)
		pListener->mouse.callMotion = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_GetButtonType(lua_State* L)
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

ETHER_API listener_SetKeyDown(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::KEYBOARD)
		pListener->keyboard.callDown = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetKeyUp(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::KEYBOARD)
		pListener->keyboard.callUp = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_GetKeyType(lua_State* L)
{
	lua_pushnumber(L, listenerManager.event.key.keysym.sym);

	return 1;
}

ETHER_API listener_GetKeyMod(lua_State* L)
{
	lua_pushnumber(L, listenerManager.event.key.keysym.mod);

	return 1;
}

ETHER_API __gc_Listener(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::MOUSE)
	{
		if (pListener->mouse.callDown != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->mouse.callDown);
		else if (pListener->mouse.callUp != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->mouse.callUp);
		else if (pListener->mouse.callMotion != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->mouse.callMotion);
	}
	else if (pListener->type == EVENT_TYPE::KEYBOARD)
	{
		if (pListener->keyboard.callDown != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->keyboard.callDown);
		else if (pListener->keyboard.callUp != LUA_REFNIL)
			luaL_unref(L, LUA_REGISTRYINDEX, pListener->keyboard.callUp);
	}

	delete pListener;

	return 0;
}