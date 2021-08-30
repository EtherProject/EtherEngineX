#include "EtherLayer.h"

ModuleLayer& ModuleLayer::Instance()
{
	static ModuleLayer* _instance = new ModuleLayer();
	return *_instance;
}

ModuleLayer::ModuleLayer()
{
	_vCMethods =
	{
		{"CreateLayer", CreateLayer}
	};

	_vMetaData =
	{
		{
			"EtherLayer",
			{},
			__gc_Layer
		}
	};
}

ETHER_API CreateLayer(lua_State* L)
{
	EtherWindow* pWindow = (EtherWindow*)(*(void**)luaL_checkudata(L, 1, "EtherWindow"));
	EtherLayer* pLayer = new EtherLayer(pWindow);
	EtherLayer** uppLayer = (EtherLayer**)lua_newuserdata(L, sizeof(EtherLayer*));
	*uppLayer = pLayer;
	luaL_getmetatable(L, "EtherLayer");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API __gc_Layer(lua_State* L)
{
	EtherLayer* pLayer = (EtherLayer*)(*(void**)luaL_checkudata(L, 1, "EtherLayer"));
	delete pLayer;

	return 0;
}