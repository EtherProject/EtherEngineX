#include "EtherNode.h"

ModuleNode& ModuleNode::Instance()
{
	static ModuleNode* _instance = new ModuleNode();
	return *_instance;
}

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
			nullptr,
			{
				{"SetPosition", node_SetPosition},
				{"GetPosition", node_GetPosition},
				{"SetParent", node_SetParent},
				{"GetParent", node_GetParent},
				{"SetDepth", node_SetDepth},
				{"GetDepth", node_GetDepth},
				{"AddChild", node_AddChild},
				{"EraseChild", node_DeleteChild}
			},
			__gc_Node
		}
	};
}

ETHER_API CreateNode(lua_State* L)
{
	EtherNode* pNode = new EtherNode();
	EtherNode** uppNode = (EtherNode**)lua_newuserdata(L, sizeof(EtherNode*));
	*uppNode = pNode;
	luaL_getmetatable(L, "EtherNode");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API node_SetPosition(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));

	pNode->copyRect.x = lua_tonumber(L, 2);
	pNode->copyRect.y = lua_tonumber(L, 3);

	return 0;
}

ETHER_API node_GetPosition(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));

	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pNode->copyRect.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pNode->copyRect.y);
	lua_settable(L, -3);

	return 1;
}

ETHER_API node_SetParent(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	EtherNode* parent = (EtherNode*)(*(void**)luaL_checkudata(L, 2, "EtherNode"));
	pNode->parent = parent;
	parent->children.push_back(pNode);

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

ETHER_API node_AddChild(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	EtherNode* pChild = (EtherNode*)(*(void**)luaL_checkudata(L, 2, "EtherNode"));
	pNode->children.push_back(pChild);
	pChild->parent = pNode;

	return 0;
}

ETHER_API node_DeleteChild(lua_State* L)
{
	using namespace std;
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	int index = lua_tonumber(L, 2) - 1;
	pNode->children[index]->parent = nullptr;
	vector<EtherNode*>::iterator iterNode = pNode->children.begin() + index;
	pNode->children.erase(iterNode);
	
	return 0;
}

ETHER_API __gc_Node(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	delete pNode;

	return 0;
}