#ifndef _NODE_H_
#define _NODE_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <vector>
#include <lua.hpp>
#include <iostream>

//节点类型,用于表明所有派生于Node类的子类
enum class NodeType
{
	Node = 0,
	Image,
	Layer
};

class EtherNode
{
public:
	//将其丢进内存管理池中
	EtherNode() {}
	//将其从内存管理池中删除
	~EtherNode() {}
	//绘制当前节点的内容
	virtual void Draw() {}

	//以父节点为基础,节点对应的矩形
	SDL_Rect copyRect = { 0,0,0,0 };
	//节点的z轴坐标,用于描述遮挡关系
	int depth = -1;
	//是否正在持续更新
	bool isRuning = false;
	//是否绘制出来
	bool isShown = false;
	//对应的图层渲染器
	SDL_Renderer* pRenderer = nullptr;
	//父节点
	EtherNode* parent = nullptr;
	//子节点向量
	std::vector<EtherNode*> children;
	//类型
	NodeType type = NodeType::Node;
};

class ModuleNode: public EtherModule
{
public:
	static ModuleNode& Instance();
	~ModuleNode() {}
private:
	ModuleNode();
};

ETHER_API CreateNode(lua_State* L);

ETHER_API node_SetPosition(lua_State* L);

ETHER_API node_GetPosition(lua_State* L);

ETHER_API node_SetParent(lua_State* L);

ETHER_API node_GetParent(lua_State* L);

ETHER_API node_SetDepth(lua_State* L);

ETHER_API node_GetDepth(lua_State* L);

ETHER_API node_AddChild(lua_State* L);

ETHER_API node_DeleteChild(lua_State* L);

ETHER_API __gc_Node(lua_State* L);

#endif // !_NODE_H_