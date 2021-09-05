#include "EtherModule.h"

EtherModule& EtherModule::Instance()
{
	static EtherModule* _instance = new EtherModule();
	return *_instance;
}

void EtherModule::PushMetaDataToGlobal(lua_State* L)
{
	for (EtherMetadata metadata : _vMetaData)
	{
		//新建一个__name = metadata.name的元表并推送到交互栈中
		luaL_newmetatable(L, metadata.name);

		//为新元表添加__index方法
		lua_pushstring(L, "__index");

		//在交互栈中开辟一个table并把metadata的所有成员函数放进去
		lua_newtable(L);
		for (luaL_Reg method : metadata.cFuns)
		{
			lua_pushstring(L, method.name);
			lua_pushcfunction(L, method.func);
			lua_settable(L, -3);
		}

		//将新元表的父类设置为该值
		if (metadata.parentName != nullptr)
			luaL_setmetatable(L, metadata.parentName);

		//新元表的__index方法是上面的成员函数表
		lua_settable(L, -3);

		//在交互栈中将GC函数设置到元表中去
		lua_pushstring(L, "__gc");
		lua_pushcfunction(L, metadata.gcFun);
		lua_settable(L, -3);
	}
}

void EtherModule::PushMoudleDataToStack(lua_State* L)
{
	//将EtherModule的宏和函数推送到交互栈,用表储存
	lua_newtable(L);

	//推送EtherModule函数
	for (luaL_Reg method : _vCMethods)
	{
		lua_pushstring(L, method.name);
		lua_pushcfunction(L, method.func);
		lua_settable(L, -3);
	}

	//推送EtherModule宏
	for (EtherMacro macro : _vMacros)
	{
		lua_pushstring(L, macro.name);
		lua_pushinteger(L, macro.value);
		lua_settable(L, -3);
	}
}