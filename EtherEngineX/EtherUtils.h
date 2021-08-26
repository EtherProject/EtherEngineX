#ifndef _UTILS_H_
#define _UTILS_H_

#include<lua.hpp>
#include<SDL.h>

//应该有一个类型检测
SDL_Point GetPointParam(lua_State* L, int index);
//应该有一个类型检测
SDL_Rect GetRectParam(lua_State* L, int index);
//应该有一个类型检测
SDL_Color GetColorParam(lua_State* L, int index);

#endif // !_UTILS_H_