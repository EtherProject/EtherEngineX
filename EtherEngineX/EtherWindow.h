#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "EtherModule.h"
#include "EtherUtils.h"
#include "EtherGraphic.h"

#include <unordered_map>
#include <vector>

class EtherWindow
{
public:
	EtherWindow(SDL_Window* _pWindow) { pWindow = _pWindow; name = nullptr; }

	~EtherWindow() { SDL_DestroyWindow(pWindow); }

	SDL_Window* pWindow = nullptr;

	SDL_Renderer* pRenderer = nullptr;

	const char* name;

	std::vector<EtherNode*> vNode;
};


class ModuleWindow: public EtherModule
{
public:
	static ModuleWindow& Instance();
	~ModuleWindow() {}
private:
	ModuleWindow();
};

enum class WINDOW
{
	POSITION_DEFAULT = INT_MIN,

	FULLSCREEN = 1004,
	FULLSCREEN_DESKTOP = 1005,
	BORDERLESS = 1006,
	RESIZABLE = 1007,
	MAXIMIZED = 1008,
	MINIMIZED = 1009,

	MODE_WINDOWED = 1013,
	MODE_FULLSCREEN = 1014,
	MODE_FULLSCREEN_DESKTOP = 1015,
	MODE_BORDERLESS = 1016,
	MODE_BORDERED = 1017,
	MODE_RESIZABLE = 1018,
	MODE_SIZEFIXED = 1019
};

//window类成员函数
ETHER_API CreateWindow(lua_State* L);

ETHER_API window_CloseWindow(lua_State* L);

ETHER_API window_GetWindowTitle(lua_State* L);

ETHER_API window_SetWindowTitle(lua_State* L);

ETHER_API window_SetWindowMode(lua_State* L);

ETHER_API window_SetWindowOpacity(lua_State* L);

ETHER_API window_GetWindowSize(lua_State* L);

ETHER_API window_SetWindowSize(lua_State* L);

ETHER_API window_GetWindowMaxSize(lua_State* L);

ETHER_API window_SetWindowMaxSize(lua_State* L);

ETHER_API window_GetWindowMinSize(lua_State* L);

ETHER_API window_SetWindowMinSize(lua_State* L);

ETHER_API window_GetWindowPosition(lua_State* L);

ETHER_API window_SetWindowPosition(lua_State* L);

ETHER_API window_GetWindowID(lua_State* L);

ETHER_API window_AddNode(lua_State* L);

ETHER_API window_DeleteNode(lua_State* L);

ETHER_API __gc_Window(lua_State* L);

#endif // !_WINDOW_H_