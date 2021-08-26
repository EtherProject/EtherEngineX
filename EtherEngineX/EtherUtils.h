#ifndef _UTILS_H_
#define _UTILS_H_

#include<lua.hpp>
#include<SDL.h>

//Ӧ����һ�����ͼ��
SDL_Point GetPointParam(lua_State* L, int index);
//Ӧ����һ�����ͼ��
SDL_Rect GetRectParam(lua_State* L, int index);
//Ӧ����һ�����ͼ��
SDL_Color GetColorParam(lua_State* L, int index);

#endif // !_UTILS_H_