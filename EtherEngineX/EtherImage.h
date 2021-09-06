#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "EtherWindow.h"
#include "EtherModule.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

class EtherImage: public EtherNode
{
public:
	EtherImage();

	~EtherImage();

	virtual void Draw();

	bool isRotated = false;
	bool isDynamic = false;
	bool isOpened = false;
	double angle = 0;

	//��ͼx����һ���м���ͼƬ
	unsigned short xAmount = 0;
	//һ���ж���֡
	unsigned short frameAmount = 0;
	//��ͼ�Ĳ����ٶ�(֡/һ��)
	unsigned short playSpeed = 0;
	//��ǰ֡
	unsigned short currentFrame = 0;
	//��ͼ��ʼ���ŵ�ʱ��(���ڼ����л���һ֡��ʲôʱ��)
	unsigned int imageFrameStart = SDL_GetTicks();
	//��ǰʱ��(���ڼ����л���һ֡��ʲôʱ��)
	unsigned int imageFrameEnd = 0;

	SDL_Surface* pSurface = nullptr;
	SDL_Texture* pTexture = nullptr;
	SDL_RendererFlip mode = SDL_FLIP_NONE;
	SDL_Rect imageRect = { 0,0,0,0 };
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

ETHER_API image_SetSize(lua_State* L);

ETHER_API image_GetSize(lua_State* L);

ETHER_API image_SetPlaySpeed(lua_State* L);

ETHER_API image_GetPlaySpeed(lua_State* L);

ETHER_API image_CreateTexture(lua_State* L);

ETHER_API image_DeleteTexture(lua_State* L);

ETHER_API __gc_Image(lua_State* L);

#endif // !_IMAGE_H_