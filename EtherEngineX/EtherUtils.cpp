#include "EtherUtils.h"

SDL_Point GetPointParam(lua_State* L, int index)
{
	SDL_Point point;

	lua_getfield(L, index, "x");
	point.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	point.y = lua_tonumber(L, -1);

	return point;
}

SDL_Rect GetRectParam(lua_State* L, int index)
{
	SDL_Rect rect;

	lua_getfield(L, index, "x");
	rect.x = lua_tonumber(L, -1);
	lua_getfield(L, index, "y");
	rect.y = lua_tonumber(L, -1);
	lua_getfield(L, index, "w");
	rect.w = lua_tonumber(L, -1);
	lua_getfield(L, index, "h");
	rect.h = lua_tonumber(L, -1);

	return rect;
}

SDL_Color GetColorParam(lua_State* L, int index)
{
	SDL_Color color;

	lua_getfield(L, index, "r");
	color.r = lua_tonumber(L, -1);
	lua_getfield(L, index, "g");
	color.g = lua_tonumber(L, -1);
	lua_getfield(L, index, "b");
	color.b = lua_tonumber(L, -1);
	lua_getfield(L, index, "a");
	color.a = lua_tonumber(L, -1);

	return color;
}