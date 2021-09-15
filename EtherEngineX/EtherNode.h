#ifndef _NODE_H_
#define _NODE_H_

#include "EtherImage.h"
#include "EtherAction.h"

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
	SDL_FRect copyRect = { 0,0,0,0 };
	//节点对应的世界矩形
	SDL_FRect worldCopyRect = { 0,0,0,0 };
	//节点的z轴坐标,用于描述遮挡关系
	int depth = -1;
	//是否持续更新
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

class EtherNodeAction
{
public:
	//NodeAction中的Action全为副本,在析构时应一一删除
	~EtherNodeAction();
	//动作是否完成,完成后在下一次会被删除
	bool isDone = false;
	//当前运行到的动作
	unsigned int index = 0;

	EtherNode* pNode;

	std::vector<EtherAction*> vAction;

	std::vector<std::function<void(EtherNode*, EtherAction*)> > vNodeAction;
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

ETHER_API node_RunAction(lua_State* L);

ETHER_API node_SetPause(lua_State* L);

ETHER_API __gc_Node(lua_State* L);

#endif // !_NODE_H_