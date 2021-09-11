#include "EtherAction.h"

ModuleAction& ModuleAction::Instance()
{
	static ModuleAction* _instance = new ModuleAction();
	return *_instance;
}

ModuleAction::ModuleAction()
{
	_vCMethods =
	{
		{"CreateMoveTo", CreateMoveTo},
		{"CreateMoveBy", CreateMoveBy},
		{"CreateSpinTo", CreateSpinTo},
		{"CreateSpinBy", CreateSpinBy},
		{"CreateFadeTo", CreateFadeTo}
	};

	_vMacros =
	{
		{"ROTATION_CLOCKWISE", (int)ROTATION::CLOCKWISE},
		{"ROTATION_ANTI_CLOCKWISE", (int)ROTATION::ANTI_CLOCKWISE}
	};

	_vMetaData =
	{
		{
			"EtherAction",
			nullptr,
			{
				{"ModifyTime", action_ModifyTime}
			},
			__gc_Action
		}
	};
}

MoveTo::MoveTo(SDL_FPoint point, unsigned int time)
{
	mPoint = point;
	last = time * ETHER_FRAME;
	type = ACTION_TYPE::MOVETO;
}

MoveBy::MoveBy(SDL_FPoint point, unsigned int time)
{
	mPoint = point;
	last = time * ETHER_FRAME;
	type = ACTION_TYPE::MOVEBY;
}

SpinTo::SpinTo(double angle, unsigned int time, Uint8 direction)
{
	mAngle = angle;
	mDirection = direction;
	last = time * ETHER_FRAME;
	type = ACTION_TYPE::SPINTO;
}

SpinBy::SpinBy(double angle, unsigned int time)
{
	mAngle = angle;
	last = time * ETHER_FRAME;
	type = ACTION_TYPE::SPINBY;
}

FadeTo::FadeTo(Uint8 alhpa, unsigned int time)
{
	mAlpha = alhpa;
	last = time * ETHER_FRAME;
	type = ACTION_TYPE::FADETO;
}

ETHER_API CreateMoveTo(lua_State* L)
{
	MoveTo* pAction = new MoveTo(GetFPointParam(L, 1), lua_tonumber(L, 2));
	EtherAction** uppAction = (EtherAction**)lua_newuserdata(L, sizeof(EtherAction*));
	*uppAction = pAction;
	luaL_getmetatable(L, "EtherAction");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API CreateMoveBy(lua_State* L)
{
	MoveBy* pAction = new MoveBy(GetFPointParam(L, 1), lua_tonumber(L, 2));
	EtherAction** uppAction = (EtherAction**)lua_newuserdata(L, sizeof(EtherAction*));
	*uppAction = pAction;
	luaL_getmetatable(L, "EtherAction");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API CreateSpinTo(lua_State* L)
{
	SpinTo* pAction = new SpinTo(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
	EtherAction** uppAction = (EtherAction**)lua_newuserdata(L, sizeof(EtherAction*));
	*uppAction = pAction;
	luaL_getmetatable(L, "EtherAction");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API CreateSpinBy(lua_State* L)
{
	SpinBy* pAction = new SpinBy(lua_tonumber(L, 1), lua_tonumber(L, 2));
	EtherAction** uppAction = (EtherAction**)lua_newuserdata(L, sizeof(EtherAction*));
	*uppAction = pAction;
	luaL_getmetatable(L, "EtherAction");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API CreateFadeTo(lua_State* L)
{
	FadeTo* pAction = new FadeTo(lua_tonumber(L, 1), lua_tonumber(L, 2));

	EtherAction** uppAction = (EtherAction**)lua_newuserdata(L, sizeof(EtherAction*));
	*uppAction = pAction;
	luaL_getmetatable(L, "EtherAction");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API action_ModifyTime(lua_State* L)
{
	EtherAction* pAction = (EtherAction*)(*(void**)lua_touserdata(L, 1));
	pAction->last = lua_tonumber(L, 2) * 60;

	return 0;
}

ETHER_API __gc_Action(lua_State* L)
{
	EtherAction* pAction = (EtherAction*)(*(void**)lua_touserdata(L, 1));
	delete pAction;

	return 0;
}