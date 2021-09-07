#ifndef _NODE_H_
#define _NODE_H_

#include "EtherModule.h"
#include "EtherUtils.h"
#include "EtherImage.h"

#include <vector>
#include <lua.hpp>

class EtherNode
{
public:
	//将其丢进内存管理池中
	EtherNode() {}
	//将其从内存管理池中删除
	~EtherNode() {}
	//绘制当前节点的内容
	virtual void Draw();
	//以父节点左上角的坐标作为参考,该节点的矩形
	SDL_Rect copyRect = { 0,0,0,0 };
	//节点对应的世界矩形
	SDL_Rect worldCopyRect = { 0,0,0,0 };
	//节点的z轴坐标,用于描述遮挡关系
	int depth = -1;
	//是否正在持续更新
	bool isRuning = true;
	//是否绘制出来
	bool isShown = true;
	//对应的渲染器
	SDL_Renderer* pRenderer = nullptr;
	//对应的图片
	EtherImage* pImage = nullptr;
	//父节点
	EtherNode* parent = nullptr;
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

ETHER_API CreateNode(lua_State* L);

ETHER_API node_SetImage(lua_State* L);

ETHER_API node_GetImage(lua_State* L);

ETHER_API node_SetCopyRect(lua_State* L);

ETHER_API node_GetCopyRect(lua_State* L);

ETHER_API node_SetParent(lua_State* L);

ETHER_API node_GetParent(lua_State* L);

ETHER_API node_SetDepth(lua_State* L);

ETHER_API node_GetDepth(lua_State* L);

ETHER_API node_AddChild(lua_State* L);

ETHER_API node_DeleteChild(lua_State* L);

ETHER_API __gc_Node(lua_State* L);

#endif // !_NODE_H_