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
	//���䶪���ڴ�������
	EtherNode();
	//������ڴ�������ɾ��
	~EtherNode();

	//�Ը��ڵ�Ϊ����,�ڵ��Ӧ������
	int x, y;
	//�ڵ��z������,���������ڵ���ϵ
	int depth;
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

ETHER_API node_CreateNode(lua_State* L);
ETHER_API __gc_Node(lua_State* L);

#endif // !_NODE_H_