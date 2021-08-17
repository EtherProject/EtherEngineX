#ifndef _MODULE_H_
#define _MODULE_H_

#include "EtherMacros.h"

#include <lua.hpp>
#include <string>
#include <vector>

//MetaData��lua��ģ��һ����
struct EtherMetadata
{
	//����
	std::string name;
	//��Ա����
	std::vector<luaL_Reg> cFuns;
	//GC����
	lua_CFunction gcFun = [](lua_State* L) -> int { return 0; };
};

class EtherModule
{
public:
	//����ģʽ
	virtual EtherModule& Instance();
	~EtherModule() {};
	//��MetaData���͵�luaȫ��
	void PushMetaDataToGlobal(lua_State* L);
	//��ModuleData���͵�����ջ
	void PushMoudleDataToStack(lua_State* L);

protected:
	EtherModule() {};
	//Module����,�����͵�����ջ
	std::vector<luaL_Reg> _vCMethods;
	//Module��,�����͵�����ջ
	std::vector<EtherMacro> _vMacros;
	//Module��(userdata),�����͵�luaȫ��
	std::vector<EtherMetadata> _vMetaData;

};

#endif // !_MODULE_H_