#ifndef _ACTION_H_
#define _ACTION_H_

#include "EtherModule.h"
#include "EtherMacros.h"
#include "EtherUtils.h"

#include <unordered_map>
#include <functional>

enum class ACTION_TYPE
{
	MOVETO = 0,
	MOVEBY,
	SPINTO,
	SPINBY,
	SCALETO,
	FADETO
};

enum class ROTATION
{
	CLOCKWISE = 0,
	ANTI_CLOCKWISE
};

class EtherAction
{
public:
	//目前进度(单位：帧)
	unsigned int progress = 0;
	//持续时间(单位：帧)
	unsigned int last = 0;
	//结束后会调用的函数
	lua_Integer callBack = LUA_REFNIL;
	//动作的类型
	ACTION_TYPE type;

	//由于暂时没有其他好主意,于是乎把所有动作的对应变量放在这了

	//用于MoveTo和MoveBy的点
	SDL_FPoint mPoint;
	
	//用于旋转的角度和方向
	double mAngle;
	Uint8 mDirection;

	//用于放大缩小的变化矩形
	float mWidth, mHeight;

	//用于alpha通道变化的值
	Uint8 mAlpha;

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

class SpinTo : public EtherAction
{
public:
	SpinTo(double angle, unsigned int time, Uint8 direction = 0);
};

class SpinBy :public EtherAction
{
public:
	SpinBy(double angle, unsigned int time);
};

class ScaleTo :public EtherAction
{
public:
	ScaleTo(float w, float h, unsigned int time);
};

class FadeTo : public EtherAction
{
public:
	FadeTo(Uint8 alpha, unsigned int time);
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

ETHER_API CreateSpinTo(lua_State* L);

ETHER_API CreateSpinBy(lua_State* L);

ETHER_API CreateScaleTo(lua_State* L);

ETHER_API CreateFadeTo(lua_State* L);

ETHER_API action_ModifyTime(lua_State* L);

ETHER_API action_SetCallback(lua_State* L);

ETHER_API __gc_Action(lua_State* L);

#endif // !_ACTION_H_