#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "EtherWindow.h"
#include "EtherModule.h"

#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class EtherImage: public EtherNode
{
public:
	EtherImage() {}

	~EtherImage();

	void Draw();

	bool isRotated = false;
	bool isDynamic = false;
	bool isOpened = false;
	double angle = 0;

	//动图x轴上一共有几张图片
	unsigned short xAmount = 0;
	//一共有多少帧
	unsigned short frameAmount = 0;
	//动图的播放速度(帧/一次)
	unsigned short playSpeed = 0;
	//当前帧(底层从0开始,lua层从1开始)
	unsigned short currentFrame = 0;
	//动图开始播放的时间(用于计算切换下一帧是什么时候)
	unsigned int imageFrameStart = SDL_GetTicks();
	//当前时间(用于计算切换下一帧是什么时候)
	unsigned int imageFrameEnd = 0;

	SDL_Surface* pSurface = nullptr;
	SDL_Texture* pTexture = nullptr;
	SDL_Renderer* pRenderer = nullptr;
	SDL_RendererFlip mode = SDL_FLIP_NONE;
	SDL_Rect imageRect;
	SDL_Point anchorPoint = { 0,0 };
};

class ModuleImage : public EtherModule
{
public:
	static ModuleImage& Instance();
	~ModuleImage() {}
private:
	ModuleImage();
};

ETHER_API LoadImageFromFile(lua_State* L);

ETHER_API LoadImageFromData(lua_State* L);

ETHER_API image_SetImageType(lua_State* L);

ETHER_API image_SetAnchorPoint(lua_State* L);

ETHER_API image_GetAnchorPoint(lua_State* L);

ETHER_API image_SetRendererFlip(lua_State* L);

ETHER_API image_SetImageRect(lua_State* L);

ETHER_API image_GetImageRect(lua_State* L);

ETHER_API image_SetCopyRect(lua_State* L);

ETHER_API image_GetCopyRect(lua_State* L);

ETHER_API image_SetPlaySpeed(lua_State* L);

ETHER_API image_GetPlaySpeed(lua_State* L);

ETHER_API image_CreateTexture(lua_State* L);

ETHER_API image_ReleaseTexture(lua_State* L);

ETHER_API __gc_Image(lua_State* L);

#endif // !_IMAGE_H_