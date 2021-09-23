#include "EtherEvent.h"

EtherListenerManager listenerManager;

ModuleEvent& ModuleEvent::Instance()
{
	static ModuleEvent* _instance = new ModuleEvent();
	return *_instance;
}

EtherListener::EtherListener(const char* paramName, EVENT_TYPE paramType)
{
	name = paramName;
	type = paramType;
}

ModuleEvent::ModuleEvent()
{
	_vCMethods =
	{
		{"CreateMouseListener", CreateMouseListener},
		{"CreateKeyboardListener", CreateKeyboardListener},
		{"CreateWindowListener", CreateWindowListener},
		{"RemoveListener", RemoveListener}
	};

	_vMacros =
	{
		//Êó±êºê
		{"MOUSE_LEFTBUTTON", SDL_BUTTON_LEFT},
		{"MOUSE_RIGHTBUTTON", SDL_BUTTON_RIGHT},
		{"MOUSE_MIDDLEBUTTON", SDL_BUTTON_MIDDLE},

		//Êó±ê¹öÂÖ·½Ïò
		{"MOUSE_WHEEL_NORMAL", SDL_MOUSEWHEEL_NORMAL},
		{"MOUSE_WHEEL_FLIPPED", SDL_MOUSEWHEEL_FLIPPED},

		//¼üÅÌºê
		//·ûºÅ°´¼ü
		{"KEY_UNKNOWN", SDLK_UNKNOWN},
		{"KEY_RETURN", SDLK_RETURN},
		{"KEY_EACAPE", SDLK_ESCAPE},
		{"KEY_BACKSPACE", SDLK_BACKSPACE},
		{"KEY_TAB", SDLK_TAB},
		{"KEY_SPACE", SDLK_SPACE},
		{"KEY_EXCLAIM", SDLK_EXCLAIM},
		{"KEY_QUOTEDBL", SDLK_QUOTEDBL},
		{"KEY_HASH", SDLK_HASH},
		{"KEY_PERCENT", SDLK_PERCENT},
		{"KEY_DOLLAR", SDLK_DOLLAR},
		{"KEY_AMPERSAND", SDLK_AMPERSAND},
		{"KEY_QUOTE", SDLK_QUOTE},
		{"KEY_LEFTPAREN", SDLK_LEFTPAREN},
		{"KEY_RIGHTPAREN", SDLK_RIGHTPAREN},
		{"KEY_ASTERISK", SDLK_ASTERISK},
		{"KEY_PLUS", SDLK_PLUS},
		{"KEY_COMMA", SDLK_COMMA},
		{"KEY_MINUS", SDLK_MINUS},
		{"KEY_PERIOD", SDLK_PERIOD},
		{"KEY_SLASH", SDLK_SLASH},
		{"KEY_COLON", SDLK_COLON},
		{"KEY_SEMICOLON", SDLK_SEMICOLON},
		{"KEY_LESS", SDLK_LESS},
		{"KEY_EQUALS", SDLK_EQUALS},
		{"KEY_GREATER", SDLK_GREATER},
		{"KEY_QUESTION", SDLK_QUESTION},
		{"KEY_AT", SDLK_AT},
		{"KEY_LEFTBRACKET", SDLK_LEFTBRACKET},
		{"KEY_RIGHTBRACKET", SDLK_RIGHTBRACKET},
		{"KEY_BACKSLASH", SDLK_BACKSLASH},
		{"KEY_CARET", SDLK_CARET},
		{"KEY_UNDERSCORE", SDLK_UNDERSCORE},
		{"KEY_BACKQUOTE", SDLK_BACKQUOTE},
		{"KEY_LCTRL", SDLK_LCTRL},
		{"KEY_RCTRL", SDLK_RCTRL},
		{"KEY_LSHIFT", SDLK_LSHIFT},
		{"KEY_RSHIFT", SDLK_RSHIFT},
		{"KEY_LALT", SDLK_LALT},
		{"KEY_RALT", SDLK_RALT},
		{"KEY_LGUI", SDLK_LGUI},
		{"KEY_RGUI", SDLK_RGUI},
		//×ÖÄ¸¼°Êý×Ö°´¼ü
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
		//mod°´¼ü
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
		{"KEY_F12", SDLK_F12},
		{"KEY_F13", SDLK_F13},
		{"KEY_F14", SDLK_F14},
		{"KEY_F15", SDLK_F15},
		{"KEY_F16", SDLK_F16},
		{"KEY_F17", SDLK_F17},
		{"KEY_F18", SDLK_F18},
		{"KEY_F19", SDLK_F19},
		{"KEY_F20", SDLK_F20},
		{"KEY_F21", SDLK_F21},
		{"KEY_F22", SDLK_F22},
		{"KEY_F23", SDLK_F23},
		{"KEY_F24", SDLK_F24},
		{"KEY_CAPSLOCK", SDLK_CAPSLOCK},
		{"KEY_PRINTSCREEN", SDLK_PRINTSCREEN},
		{"KEY_SCROLLLOCK", SDLK_SCROLLLOCK},
		{"KEY_PAUSE", SDLK_PAUSE},
		{"KEY_INSERT", SDLK_INSERT},
		{"KEY_HOME", SDLK_HOME},
		{"KEY_PAGEUP", SDLK_PAGEUP},
		{"KEY_DELETE", SDLK_DELETE},
		{"KEY_END", SDLK_END},
		{"KEY_PAGEDOWN", SDLK_PAGEDOWN},
		{"KEY_RIGHT", SDLK_RIGHT},
		{"KEY_LEFT", SDLK_LEFT},
		{"KEY_DOWN", SDLK_DOWN},
		{"KEY_UP", SDLK_UP},
		//Ð¡¼üÅÌ
		{"KEY_NUMLOCKCLEAR", SDLK_NUMLOCKCLEAR},
		{"KEY_KP_DIVIDE", SDLK_KP_DIVIDE},
		{"KEY_KP_MULTIPLY", SDLK_KP_MULTIPLY},
		{"KEY_KP_MINUS", SDLK_KP_MINUS},
		{"KEY_KP_PLUS", SDLK_KP_PLUS},
		{"KEY_KP_ENTER", SDLK_KP_ENTER},
		{"KEY_KP_0", SDLK_KP_0},
		{"KEY_KP_1", SDLK_KP_1},
		{"KEY_KP_2", SDLK_KP_2},
		{"KEY_KP_3", SDLK_KP_3},
		{"KEY_KP_4", SDLK_KP_4},
		{"KEY_KP_5", SDLK_KP_5},
		{"KEY_KP_6", SDLK_KP_6},
		{"KEY_KP_7", SDLK_KP_7},
		{"KEY_KP_8", SDLK_KP_8},
		{"KEY_KP_9", SDLK_KP_9},
		{"KEY_KP_PERIOD", SDLK_KP_PERIOD},

		//ÐÞÊÎ¼ü
		{"KEY_MOD_NONE", KMOD_NONE},
		{"KEY_MOD_LSHIFT", KMOD_LSHIFT},
		{"KEY_MOD_RSHIFT", KMOD_RSHIFT},
		{"KEY_MOD_LCTRL", KMOD_LCTRL},
		{"KEY_MOD_RCTRL", KMOD_RCTRL},
		{"KEY_MOD_LALT", KMOD_LALT},
		{"KEY_MOD_RALT", KMOD_RALT},
		{"KEY_MOD_LGUI", KMOD_LGUI},
		{"KEY_MOD_RGUI", KMOD_RGUI},
		{"KEY_MOD_NUM", KMOD_NUM},
		{"KEY_MOD_CAPS", KMOD_CAPS},
		{"KEY_MOD_RESERVED", KMOD_RESERVED},
		{"KEY_MOD_CTRL", KMOD_CTRL},
		{"KEY_MOD_SHIFT", KMOD_SHIFT},
		{"KEY_MOD_ALT", KMOD_ALT},
		{"KEY_MOD_GUI", KMOD_GUI}
	};

	_vMetaData =
	{
		{
			"EtherListener",
			nullptr,
			{
				{"GetName", listener_GetName},

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
				{"GetKeyMod", listener_GetKeyMod},

			//´°¿ÚÊÂ¼þ
				{"SetWindowShown", listener_SetWindowShown},
				{"SetWindowHidden", listener_SetWindowHidden},
				{"SetWindowEnter", listener_SetWindowEnter},
				{"SetWindowLeave", listener_SetWindowLeave},
				{"SetWindowFocusGained", listener_SetWindowFocusGained},
				{"SetWindowFocusLost", listener_SetWindowFocusLost},
				{"SetWindowClose", listener_SetWindowClose},
				{"SetWindowResize", listener_SetWindowResize},
				{"SetWindowMove", listener_SetWindowMove},

				{"GetWindowEventID", listener_GetEventWindowID}
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

void WindowListener::Callback(lua_State* L, SDL_Event* event)
{
	if (event->window.event == SDL_WINDOWEVENT_SHOWN && callShown != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callShown);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_HIDDEN && callHidden != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callHidden);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_ENTER && callEnter != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callEnter);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_LEAVE && callLeave != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callLeave);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED && callFocusGained != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callFocusGained);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_FOCUS_LOST && callFocusLost != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callFocusLost);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_CLOSE && callClose != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callClose);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED && callResize != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callResize);
		lua_pcall(L, 0, 0, 0);
	}
	else if (event->window.event == SDL_WINDOWEVENT_MOVED && callMove != LUA_REFNIL)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callMove);
		lua_pcall(L, 0, 0, 0);
	}
}

ETHER_API CreateMouseListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	EtherListener* pListener = new EtherListener(name, EVENT_TYPE::MOUSE);
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

	EtherListener* pListener = new EtherListener(name, EVENT_TYPE::KEYBOARD);
	listenerManager.mapListener[name] = pListener;

	EtherListener** uppListener = (EtherListener**)lua_newuserdata(L, sizeof(EtherListener*));
	*uppListener = pListener;
	luaL_getmetatable(L, "EtherListener");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API CreateWindowListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);

	EtherListener* pListener = new EtherListener(name, EVENT_TYPE::WINDOW);
	listenerManager.mapListener[name] = pListener;

	EtherListener** uppListener = (EtherListener**)lua_newuserdata(L, sizeof(EtherListener*));
	*uppListener = pListener;
	luaL_getmetatable(L, "EtherListener");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API RemoveListener(lua_State* L)
{
	const char* name = lua_tostring(L, 1);
	auto iter = listenerManager.mapListener.find(name);
	(*iter).second->~EtherListener();
	listenerManager.mapListener.erase(iter);

	return 0;
}

ETHER_API listener_GetName(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));
	lua_pushstring(L, pListener->name);

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

ETHER_API listener_SetWindowShown(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callShown = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowHidden(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callHidden = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowEnter(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callEnter = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowLeave(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callLeave = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowFocusGained(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callFocusGained = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowFocusLost(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callFocusLost = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowClose(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callClose = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowResize(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callResize = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_SetWindowMove(lua_State* L)
{
	EtherListener* pListener = (EtherListener*)(*(void**)luaL_checkudata(L, 1, "EtherListener"));

	if (pListener->type == EVENT_TYPE::WINDOW)
		pListener->window.callMove = luaL_ref(L, LUA_REGISTRYINDEX);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Callback Failed", "Type mismatch", nullptr);

	return 0;
}

ETHER_API listener_GetEventWindowID(lua_State* L)
{
	lua_pushnumber(L, listenerManager.event.window.windowID);

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