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
		{"CreateMoveBy", CreateMoveBy}
	};

	_vMetaData =
	{
		{
			"EtherAction",
			nullptr,
			{
				{},
				{}
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
	MoveTo* pAction = new MoveTo(GetFPointParam(L, 1), lua_tonumber(L, 2));
	EtherAction** uppAction = (EtherAction**)lua_newuserdata(L, sizeof(EtherAction*));
	*uppAction = pAction;
	luaL_getmetatable(L, "EtherAction");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API __gc_Action(lua_State* L)
{
	EtherAction* pAction = (EtherAction*)(*(void**)lua_touserdata(L, 1));
	delete pAction;

	return 0;
}