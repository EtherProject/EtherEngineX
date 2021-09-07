#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "EtherModule.h"
#include "EtherUtils.h"
#include "EtherNode.h"

#include <string>
#include <unordered_map>
#include <vector>

class EtherLayer
{
public:
	EtherLayer() {}

	~EtherLayer() {}

	void Draw();

	SDL_Renderer* pRenderer = nullptr;

	std::vector<EtherNode*> children;
};

class EtherWindow
{
public:
	EtherWindow(SDL_Window* _pWindow) { pWindow = _pWindow; name = nullptr; }

	~EtherWindow() { SDL_DestroyWindow(pWindow); }

	SDL_Window* pWindow = nullptr;

	SDL_Renderer* pRenderer = nullptr;

	const char* name;

	std::vector<EtherLayer*> vLayer;
};


class ModuleWindow: public EtherModule
{
public:
	static ModuleWindow& Instance();
	~ModuleWindow() {}
private:
	ModuleWindow();
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

ETHER_API window_CreateLayer(lua_State* L);

ETHER_API window_DeleteLayer(lua_State* L);

ETHER_API __gc_Window(lua_State* L);

ETHER_API layer_AddNode(lua_State* L);

ETHER_API layer_DeleteNode(lua_State* L);

ETHER_API __gc_Layer(lua_State* L);

#endif // !_WINDOW_H_