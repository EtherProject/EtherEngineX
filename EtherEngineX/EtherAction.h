#ifndef _ACTION_H_
#define _ACTION_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <unordered_map>

enum class ACTION_TYPE
{
	MOVETO = 0,
	MOVEBY,
};

class EtherAction
{
public:
	//目前进度(单位：帧)
	unsigned int progress = 0;
	//持续时间(单位：帧)
	unsigned int last = 0;
	//结束后会调用的函数
	lua_CFunction stop = [](lua_State* L) -> int { return 0; };
	//动作的类型
	ACTION_TYPE type;

	//由于暂时没有其他好主意,于是乎把所有动作的对应变量放在这了
	SDL_FPoint mPoint;
	double mAngle;

protected:
	EtherAction() {}
};

class MoveTo: public EtherAction
{
public:
	MoveTo(SDL_FPoint point, unsigned int time);
};

class MoveBy : public EtherAction
{
public:
	MoveBy(SDL_FPoint point, unsigned int time);
};

class ModuleAction : public EtherModule
{
public:
	static ModuleAction& Instance();
	~ModuleAction() {}
private:
	ModuleAction();
};

ETHER_API CreateMoveTo(lua_State* L);

ETHER_API CreateMoveBy(lua_State* L);

ETHER_API __gc_Action(lua_State* L);

#endif // !_ACTION_H_