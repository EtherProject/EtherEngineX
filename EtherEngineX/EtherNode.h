#ifndef _NODE_H_
#define _NODE_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <vector>
#include <lua.hpp>
#include <iostream>

//�ڵ�����,���ڱ�������������Node�������
enum class NodeType
{
	Node = 0,
	Image,
	Layer
};

class EtherNode
{
public:
	//���䶪���ڴ�������
	EtherNode() {}
	//������ڴ�������ɾ��
	~EtherNode() {}
	//���Ƶ�ǰ�ڵ������
	virtual void Draw() {}

	//�Ը��ڵ�Ϊ����,�ڵ��Ӧ�ľ���
	SDL_Rect copyRect = { 0,0,0,0 };
	//�ڵ��z������,���������ڵ���ϵ
	int depth = -1;
	//�Ƿ����ڳ�������
	bool isRuning = false;
	//�Ƿ���Ƴ���
	bool isShown = false;
	//��Ӧ��ͼ����Ⱦ��
	SDL_Renderer* pRenderer = nullptr;
	//���ڵ�
	EtherNode* parent = nullptr;
	//�ӽڵ�����
	std::vector<EtherNode*> children;
	//����
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