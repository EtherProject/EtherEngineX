#ifndef _LAYER_H_
#define _LAYER_H_

#include "EtherNode.h"

#include <vector>
#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>

//每个图层对应着一个渲染器
class EtherLayer : public EtherNode
{
public:
	EtherLayer(SDL_Window* pWindow);
	virtual ~EtherLayer();

	SDL_Renderer* pRenderer;
	std::vector<EtherNode*> vAllNode;
};

class ModuleLayer : public EtherModule
{
public:
	static ModuleLayer& Instance();
	~ModuleLayer() {}
private:
	ModuleLayer();
};

ETHER_API CreateLayer(lua_State* L);

ETHER_API layer_AddNode(lua_State* L);

ETHER_API layer_EraseNode(lua_State* L);

ETHER_API __gc_Layer(lua_State* L);

#endif // !_LAYER_H_