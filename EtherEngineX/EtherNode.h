#ifndef _NODE_H_
#define _NODE_H_

#include "EtherData.h"
#include "EtherMacros.h"

#include <vector>
#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class EtherNode :public EtherData
{
public:
	//将其丢进内存管理池中
	EtherNode();
	//将其从内存管理池中删除
	~EtherNode();

	//以父节点为基础,节点对应的坐标
	int x, y;
	//节点的z轴坐标,用于描述遮挡关系
	int depth;
	//父节点
	EtherNode* parent;
	//子节点向量
	std::vector<EtherNode*> children;
};

class ModuleNode: public EtherModule
{
public:
	static ModuleNode& Instance();
	~ModuleNode() {}
private:
	ModuleNode();
};

ETHER_API node_CreateNode(lua_State* L);
ETHER_API __gc_Node(lua_State* L);

#endif // !_NODE_H_