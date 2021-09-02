#include "EtherImage.h"

ModuleImage& ModuleImage::Instance()
{
	static ModuleImage* _instance = new ModuleImage();
	return *_instance;
}

ModuleImage::ModuleImage()
{
	_vCMethods =
	{
		{"LoadImageFromFile", LoadImageFromFile},
		{"LoadImageFromData", LoadImageFromData}
	};

	_vMetaData =
	{
		{
			"EtherImage",
			{
				{"CreateTexture", image_CreateTexture},
				{"ReleaseTexture", image_ReleaseTexture}
			},
			__gc_Image
		}
	};
}

EtherImage::~EtherImage()
{
	if (isOpened) SDL_DestroyTexture(pTexture);
}

//这里应当再实现子节点随父节点的移动而移动
void EtherImage::Draw()
{
	using namespace std;
	if (isRotated)
	{
		if (isDynamic)
		{
			imageFrameEnd = SDL_GetTicks();
			if ((imageFrameEnd - imageFrameStart) / 60 >= playSpeed)
			{
				imageFrameStart = imageFrameEnd;
				imageRect.x = (currentFrame % xAmount) * imageRect.w;
				imageRect.y = (currentFrame / xAmount) * imageRect.h;
				SDL_RenderCopyEx(pRenderer, pTexture, &imageRect, &copyRect, angle, &anchorPoint, mode);
				currentFrame = (currentFrame + 1) % frameAmount;
			}
		}
		else
			SDL_RenderCopyEx(pRenderer, pTexture, &imageRect, &copyRect, angle, &anchorPoint, mode);
	}
	else
	{
		if (isDynamic)
		{
			imageFrameEnd = SDL_GetTicks();
			if ((imageFrameEnd - imageFrameStart) / 60 >= playSpeed)
			{
				imageFrameStart = imageFrameEnd;
				imageRect.x = (currentFrame % xAmount) * imageRect.w;
				imageRect.y = (currentFrame / xAmount) * imageRect.h;
				SDL_RenderCopy(pRenderer, pTexture, &imageRect, &copyRect);
				currentFrame = (currentFrame + 1) % frameAmount;
			}
		}
		else
			SDL_RenderCopy(pRenderer, pTexture, &imageRect, &copyRect);
	}
	if (!children.empty())
		for (vector<EtherNode*>::iterator iter = children.begin(); iter != children.end(); iter++)
			(*iter)->Draw();
}

ETHER_API LoadImageFromFile(lua_State* L)
{
	EtherImage* pImage = new EtherImage();

	SDL_Surface* pSurface = IMG_Load(luaL_checkstring(L, 1));
	luaL_argcheck(L, pSurface, 1, "load image from file failed");

	pImage->pSurface = pSurface;

	EtherImage** uppImage = (EtherImage**)lua_newuserdata(L, sizeof(EtherImage*));
	*uppImage = pImage;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API LoadImageFromData(lua_State* L)
{
	EtherImage* pImage = new EtherImage();

	size_t size = 0;
	SDL_Surface* pSurface = IMG_Load_RW(SDL_RWFromMem((void*)luaL_checklstring(L, 1, &size), size), 1);
	luaL_argcheck(L, pSurface, 1, "load image from data failed");

	pImage->pSurface = pSurface;

	SDL_Surface** uppSurface = (SDL_Surface**)lua_newuserdata(L, sizeof(SDL_Surface*));
	*uppSurface = pSurface;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API image_CreateTexture(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	EtherLayer* pLayer = (EtherLayer*)(*(void**)luaL_checkudata(L, 1, "EtherLayer"));
	pImage->pTexture = SDL_CreateTextureFromSurface(pLayer->pRenderer, pImage->pSurface);
	pImage->pRenderer = pLayer->pRenderer;
	pImage->isOpened = true;

	return 0;
}

ETHER_API image_ReleaseTexture(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	SDL_DestroyTexture(pImage->pTexture);
	pImage->isOpened = false;

	return 0;
}

ETHER_API __gc_Image(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	delete pImage;

	return 0;
}