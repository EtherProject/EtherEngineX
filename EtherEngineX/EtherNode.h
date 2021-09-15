#ifndef _NODE_H_
#define _NODE_H_

#include "EtherImage.h"
#include "EtherAction.h"

#include <vector>
#include <lua.hpp>

class EtherNode
{
public:
	//���䶪���ڴ�������
	EtherNode() {}
	//������ڴ�������ɾ��
	~EtherNode() {}
	//���Ƶ�ǰ�ڵ������
	virtual void Draw();
	//�Ը��ڵ����Ͻǵ�������Ϊ�ο�,�ýڵ�ľ���
	SDL_FRect copyRect = { 0,0,0,0 };
	//�ڵ��Ӧ���������
	SDL_FRect worldCopyRect = { 0,0,0,0 };
	//�ڵ��z������,���������ڵ���ϵ
	int depth = -1;
	//�Ƿ��������
	bool isRuning = true;
	//�Ƿ���Ƴ���
	bool isShown = true;
	//��Ӧ����Ⱦ��
	SDL_Renderer* pRenderer = nullptr;
	//��Ӧ��ͼƬ
	EtherImage* pImage = nullptr;
	//���ڵ�
	EtherNode* parent = nullptr;
	//�ӽڵ�����
	std::vector<EtherNode*> children;
};

class EtherNodeAction
{
public:
	//NodeAction�е�ActionȫΪ����,������ʱӦһһɾ��
	~EtherNodeAction();
	//�����Ƿ����,��ɺ�����һ�λᱻɾ��
	bool isDone = false;
	//��ǰ���е��Ķ���
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