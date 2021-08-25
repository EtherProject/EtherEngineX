#include "EtherNode.h"
using namespace std;

ModuleNode::ModuleNode()
{
	_vMetaData =
	{
		{
			"EtherNode",
			{
				{"CreateNode", node_CreateNode}
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

EtherNode::EtherNode() : EtherData(), x(0), y(0), depth(0), parent(nullptr)
{
	type = DataType::Node;
	dataInUse[type].push_back(*this);
	key = dataInUse[type].size() - 1;
}

EtherNode::~EtherNode()
{
	vector<EtherData>::iterator temp = dataNotInUse[type].begin() + key;
	dataNotInUse[type].erase(temp);
}

ETHER_API node_CreateNode(lua_State* L)
{
	EtherNode* pNode = new EtherNode;
	EtherNode** uppNode = (EtherNode**)lua_newuserdata(L, sizeof(EtherNode*));
	*uppNode = pNode;
	luaL_getmetatable(L, "EtherNode");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API __gc_Node(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)luaL_checkudata(L, 1, "EtherNode"));
	delete pNode;

	return 0;
}