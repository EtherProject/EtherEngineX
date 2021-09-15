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
	//Ŀǰ����(��λ��֡)
	unsigned int progress = 0;
	//����ʱ��(��λ��֡)
	unsigned int last = 0;
	//���������õĺ���
	lua_Integer callBack = LUA_REFNIL;
	//����������
	ACTION_TYPE type;

	//������ʱû������������,���Ǻ������ж����Ķ�Ӧ������������

	//����MoveTo��MoveBy�ĵ�
	SDL_FPoint mPoint;
	
	//������ת�ĽǶȺͷ���
	double mAngle;
	Uint8 mDirection;

	//���ڷŴ���С�ı仯����
	float mWidth, mHeight;

	//����alphaͨ���仯��ֵ
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