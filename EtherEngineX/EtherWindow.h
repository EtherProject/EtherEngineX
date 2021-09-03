#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "EtherModule.h"
#include "EtherNode.h"
#include "EtherUtils.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//每个图层对应着一个渲染器
class EtherLayer : public EtherNode
{
public:
	EtherLayer(SDL_Window* pWindow);
	virtual ~EtherLayer();
	void Draw();

	SDL_Renderer* pRenderer;
	std::vector<EtherNode*> vAllNode;
};

//每个窗口都可以拥有多个图层
class EtherWindow
{
public:
	EtherWindow(SDL_Window* _pWindow) { pWindow = _pWindow; name = nullptr; }

	~EtherWindow() { SDL_DestroyWindow(pWindow); }

	SDL_Window* pWindow = nullptr;

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

ETHER_API __gc_Window(lua_State* L);

//layer类成员函数
ETHER_API layer_AddNode(lua_State* L);

ETHER_API layer_EraseNode(lua_State* L);

ETHER_API __gc_Layer(lua_State* L);

#endif // !_WINDOW_H_