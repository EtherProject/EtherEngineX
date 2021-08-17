#ifndef _MODULE_H_
#define _MODULE_H_

#include "EtherMacros.h"

#include <lua.hpp>
#include <string>
#include <vector>

//MetaData在lua中模拟一个类
struct EtherMetadata
{
	//类名
	std::string name;
	//成员函数
	std::vector<luaL_Reg> cFuns;
	//GC函数
	lua_CFunction gcFun = [](lua_State* L) -> int { return 0; };
};

class EtherModule
{
public:
	//单例模式
	virtual EtherModule& Instance();
	~EtherModule() {};
	//将MetaData推送到lua全局
	void PushMetaDataToGlobal(lua_State* L);
	//将ModuleData推送到交互栈
	void PushMoudleDataToStack(lua_State* L);

protected:
	EtherModule() {};
	//Module函数,被推送到交互栈
	std::vector<luaL_Reg> _vCMethods;
	//Module宏,被推送到交互栈
	std::vector<EtherMacro> _vMacros;
	//Module类(userdata),被推送到lua全局
	std::vector<EtherMetadata> _vMetaData;

};

#endif // !_MODULE_H_