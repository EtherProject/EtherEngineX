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
		//�½�һ��__name = metadata.name��Ԫ�����͵�����ջ��
		luaL_newmetatable(L, metadata.name);

		//Ϊ��Ԫ�����__index����
		lua_pushstring(L, "__index");

		//�ڽ���ջ�п���һ��table����metadata�����г�Ա�����Ž�ȥ
		lua_newtable(L);
		for (luaL_Reg method : metadata.cFuns)
		{
			lua_pushstring(L, method.name);
			lua_pushcfunction(L, method.func);
			lua_settable(L, -3);
		}

		//����Ԫ��ĸ�������Ϊ��ֵ
		if (metadata.parentName != nullptr)
			luaL_setmetatable(L, metadata.parentName);

		//��Ԫ���__index����������ĳ�Ա������
		lua_settable(L, -3);

		//�ڽ���ջ�н�GC�������õ�Ԫ����ȥ
		lua_pushstring(L, "__gc");
		lua_pushcfunction(L, metadata.gcFun);
		lua_settable(L, -3);
	}
}

void EtherModule::PushMoudleDataToStack(lua_State* L)
{
	//��EtherModule�ĺ�ͺ������͵�����ջ,�ñ���
	lua_newtable(L);

	//����EtherModule����
	for (luaL_Reg method : _vCMethods)
	{
		lua_pushstring(L, method.name);
		lua_pushcfunction(L, method.func);
		lua_settable(L, -3);
	}

	//����EtherModule��
	for (EtherMacro macro : _vMacros)
	{
		lua_pushstring(L, macro.name);
		lua_pushinteger(L, macro.value);
		lua_settable(L, -3);
	}
}