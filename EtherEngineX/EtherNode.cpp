#include "EtherNode.h"

using namespace std;

extern unordered_map<DataType, vector<EtherData*>> dataInUse;
extern unordered_map<DataType, vector<EtherData*>> dataNotInUse;

ModuleNode::ModuleNode()
{
	_vCMethods =
	{
		{"CreateNode", CreateNode}
	};

	_vMetaData =
	{
		{
			"EtherNode",
			{
				{"SetPosition", node_SetPosition},
				{"GetPosition", node_GetPosition},
				{"SetParent", node_SetParent},
				{"GetParent", node_GetParent},
				{"SetDepth", node_SetDepth},
				{"GetDepth", node_GetDepth},
				{"Release", node_Release}
			},
			__gc_Node
		}
	};
}

ModuleNode& ModuleNode::Instance()
{
	static ModuleNode* _instance = new ModuleNode();
	return *_instance;
}

//EtherNode类

EtherNode::EtherNode() : EtherData(), x(0), y(0), depth(0), isRuning(1), parent(nullptr)
{
	type = DataType::Node;
	dataInUse[type].push_back(this);
	key = dataInUse[type].size() - 1;
}

EtherNode::~EtherNode()
{
	//负责将该对象从内存池里面弹出来
	vector<EtherData*>::iterator temp = dataNotInUse[type].begin() + key;
	dataNotInUse[type].erase(temp);
}

ETHER_API CreateNode(lua_State* L)
{
	EtherNode* pNode = new EtherNode;
	EtherNode** uppNode = (EtherNode**)lua_newuserdata(L, sizeof(EtherNode*));
	*uppNode = pNode;
	luaL_getmetatable(L, "EtherNode");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API node_SetPosition(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	SDL_Point point = GetPointParam(L, 2);
	pNode->x = point.x;
	pNode->y = point.y;

	return 0;
}

ETHER_API node_GetPosition(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pNode->x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pNode->y);
	lua_settable(L, -3);

	return 1;
}

ETHER_API node_SetParent(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	EtherNode* parent = (EtherNode*)(*(void**)luaL_checkudata(L, 2, "EtherNode"));
	pNode->parent = parent;

	return 0;
}

ETHER_API node_GetParent(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	EtherNode** uppNode = (EtherNode**)lua_newuserdata(L, sizeof(EtherNode*));
	*uppNode = pNode->parent;
	luaL_getmetatable(L, "EtherNode");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API node_SetDepth(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	int depth = lua_tonumber(L, 2);
	pNode->depth = depth;

	return 0;
}

ETHER_API node_GetDepth(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	lua_pushnumber(L, pNode->depth);

	return 1;
}

ETHER_API node_Release(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	vector<EtherData*>::iterator temp = dataInUse[pNode->type].begin() + pNode->key;
	dataInUse[pNode->type].erase(temp);
	dataNotInUse[pNode->type].push_back(pNode);
	pNode->key = dataNotInUse[pNode->type].size() - 1;

	return 0;
}

ETHER_API __gc_Node(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	delete pNode;

	return 0;
}