#ifndef _NODE_H_
#define _NODE_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <vector>
#include <lua.hpp>

class EtherNode
{
public:
	//���䶪���ڴ�������
	EtherNode();
	//������ڴ�������ɾ��
	~EtherNode();
	//���Ƶ�ǰ�ڵ������
	virtual void Draw() {}

	//�Ը��ڵ�Ϊ����,�ڵ��Ӧ������
	int x, y;
	//�ڵ��z������,���������ڵ���ϵ
	int depth;
	//�Ƿ����ڳ�������
	bool isRuning;
	//�Ƿ���Ƴ���
	bool isShown;
	//���ڵ�
	EtherNode* parent;
	//�ӽڵ�����
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

ETHER_API node_SetPosition(lua_State* L);

ETHER_API node_GetPosition(lua_State* L);

ETHER_API node_SetParent(lua_State* L);

ETHER_API node_GetParent(lua_State* L);

ETHER_API node_SetDepth(lua_State* L);

ETHER_API node_GetDepth(lua_State* L);

ETHER_API node_AddChild(lua_State* L);

//ɾ��λ���ӽڵ�������ָ���������ӽڵ�
ETHER_API node_EraseChild(lua_State* L);

ETHER_API __gc_Node(lua_State* L);

#endif // !_NODE_H_