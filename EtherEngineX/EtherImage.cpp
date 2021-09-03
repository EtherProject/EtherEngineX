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

	_vMacros =
	{
		{"FLIP_HORIZONTAL", SDL_FLIP_HORIZONTAL},
		{"FLIP_VERTICAL", SDL_FLIP_VERTICAL},
		{"FLIP_NONE", SDL_FLIP_NONE}
	};

	_vMetaData =
	{
		{
			"EtherImage",
			{
				{"CreateTexture", image_CreateTexture},
				{"ReleaseTexture", image_ReleaseTexture},
				{"SetImageType", image_SetImageType},
				{"SetAnchorPoint", image_SetAnchorPoint},
				{"GetAnchorPoint", image_GetAnchorPoint},
				{"SetRendererFlip", image_SetRendererFlip},
				{"SetImageRect", image_SetImageRect},
				{"GetImageRect", image_GetImageRect},
				{"SetCopyRect", image_SetCopyRect},
				{"GetCopyRect", image_GetCopyRect},
				{"SetPlaySpeed", image_SetPlaySpeed},
				{"GetPlaySpeed", image_GetPlaySpeed}
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

	pImage->pSurface = IMG_Load(luaL_checkstring(L, 1));
	luaL_argcheck(L, pImage->pSurface, 1, "load image from file failed");

	pImage->imageRect.x = 0; pImage->imageRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w; pImage->imageRect.h = pImage->pSurface->h;
	pImage->copyRect.x = 0; pImage->copyRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w; pImage->imageRect.h = pImage->pSurface->h;

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
	pImage->pSurface = IMG_Load_RW(SDL_RWFromMem((void*)luaL_checklstring(L, 1, &size), size), 1);
	luaL_argcheck(L, pImage->pSurface, 1, "load image from data failed");

	pImage->imageRect.x = 0; pImage->imageRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w; pImage->imageRect.h = pImage->pSurface->h;
	pImage->copyRect.x = 0; pImage->copyRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w; pImage->imageRect.h = pImage->pSurface->h;

	EtherImage** uppImage = (EtherImage**)lua_newuserdata(L, sizeof(EtherImage*));
	*uppImage = pImage;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API image_SetImageType(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	pImage->isDynamic = lua_toboolean(L, 2);

	return 0;
}

ETHER_API image_SetAnchorPoint(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	pImage->anchorPoint.x = lua_tonumber(L, 2);
	pImage->anchorPoint.y = lua_tonumber(L, 3);

	return 0;
}

ETHER_API image_GetAnchorPoint(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pImage->anchorPoint.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pImage->anchorPoint.y);
	lua_settable(L, -3);

	return 1;
}

ETHER_API image_SetRendererFlip(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));

	lua_pushnil(L);
	while (lua_next(L, 2))
	{
		if (!lua_isnumber(L, -1))
		{
			luaL_error(L, "bad argument #1 to 'SetRendererFlip' (table elements must be MACRO number, got %s)", luaL_typename(L, -1));
		}
		else
		{
			switch ((int)lua_tonumber(L, -1))
			{
			case SDL_FLIP_HORIZONTAL:
				pImage->mode = (SDL_RendererFlip)(pImage->mode | SDL_FLIP_HORIZONTAL);
				break;
			case SDL_FLIP_VERTICAL:
				pImage->mode = (SDL_RendererFlip)(pImage->mode | SDL_FLIP_VERTICAL);
				break;
			case SDL_FLIP_NONE:
				pImage->mode = (SDL_RendererFlip)(pImage->mode | SDL_FLIP_NONE);
				break;
			default:
				luaL_error(L, "bad argument #1 to 'SetRendererFlip' (table elements must be MACRO number, got %s)", luaL_typename(L, -1));
				break;
			}
		}
		lua_pop(L, 1);
	}

	return 0;
}

ETHER_API image_SetImageRect(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	SDL_Rect reshapeRect = GetRectParam(L, 2);
	pImage->imageRect = reshapeRect;

	return 0;
}

ETHER_API image_GetImageRect(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));

	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pImage->imageRect.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pImage->imageRect.y);
	lua_settable(L, -3);
	lua_pushstring(L, "w");
	lua_pushnumber(L, pImage->imageRect.w);
	lua_settable(L, -3);
	lua_pushstring(L, "h");
	lua_pushnumber(L, pImage->imageRect.h);
	lua_settable(L, -3);

	return 1;
}

ETHER_API image_SetCopyRect(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	SDL_Rect rect = GetRectParam(L, 2);

	pImage->copyRect = rect;

	return 0;
}

ETHER_API image_GetCopyRect(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));

	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pImage->copyRect.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pImage->copyRect.y);
	lua_settable(L, -3);
	lua_pushstring(L, "w");
	lua_pushnumber(L, pImage->copyRect.w);
	lua_settable(L, -3);
	lua_pushstring(L, "h");
	lua_pushnumber(L, pImage->copyRect.h);
	lua_settable(L, -3);

	return 1;
}

ETHER_API image_SetPlaySpeed(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	unsigned short playSpeed = lua_tonumber(L, 2);
	pImage->playSpeed = playSpeed;

	return 0;
}

ETHER_API image_GetPlaySpeed(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	lua_pushnumber(L, pImage->playSpeed);

	return 1;
}

ETHER_API image_CreateTexture(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	EtherLayer* pLayer = (EtherLayer*)(*(void**)luaL_checkudata(L, 2, "EtherLayer"));
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