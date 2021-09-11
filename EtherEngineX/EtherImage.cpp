#include "EtherImage.h"

ModuleImage& ModuleImage::Instance()
{
	static ModuleImage* _instance = new ModuleImage();
	return *_instance;
}

ModuleImage::ModuleImage()
{
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

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
			nullptr,
			{
				{"SetImageDynamic", image_SetImageDynamic},
				{"SetRendererFlip", image_SetRendererFlip},
				{"SetAnchorPoint", image_SetAnchorPoint},
				{"GetAnchorPoint", image_GetAnchorPoint},
				{"SetImageRect", image_SetImageRect},
				{"GetImageRect", image_GetImageRect},
				{"SetAlpha", image_SetAlpha},
				{"GetAlpha", image_GetAlpha},
				{"SetPlaySpeed", image_SetPlaySpeed},
				{"GetPlaySpeed", image_GetPlaySpeed},
				{"SetCurrentFrame", image_SetCurrentFrame},
				{"GetCurrentFrame", image_GetCurrentFrame},
				{"SetAngle", image_SetAngle},
				{"GetAngle", image_GetAngle}
			},
			__gc_Image
		}
	};
}

EtherImage::~EtherImage()
{
	if (isOpened) SDL_DestroyTexture(pTexture);
}

ETHER_API LoadImageFromFile(lua_State* L)
{
	EtherImage* pImage = new EtherImage();

	pImage->pSurface = IMG_Load(luaL_checkstring(L, 1));
	luaL_argcheck(L, pImage->pSurface, 1, "load image from data failed");

	pImage->imageRect.x = 0;
	pImage->imageRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w;
	pImage->imageRect.h = pImage->pSurface->h;

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

	pImage->imageRect.x = 0;
	pImage->imageRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w;
	pImage->imageRect.h = pImage->pSurface->h;

	EtherImage** uppImage = (EtherImage**)lua_newuserdata(L, sizeof(EtherImage*));
	*uppImage = pImage;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API image_SetImageDynamic(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	pImage->isDynamic = lua_toboolean(L, 2);

	if (pImage->isDynamic)
	{
		if (lua_isnumber(L, 3))
		{
			//如果是动图则需要自己告诉程序一共有多少帧
			//以及动图每帧图片的大小
			pImage->frameAmount = lua_tonumber(L, 3);
			pImage->imageRect.w = lua_tonumber(L, 4);
			pImage->imageRect.h = lua_tonumber(L, 5);
			pImage->xAmount = pImage->pSurface->w / pImage->imageRect.w;
		}
		else
		{
			pImage->isDynamic = false;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured:", "The frame's amount must be a number!", nullptr);
		}
	}
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

ETHER_API image_SetAlpha(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));

	if (pImage->isOpened)
		SDL_SetTextureAlphaMod(pImage->pTexture, luaL_checknumber(L, 2));
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Setting Alpha", "You can't set alpha for a unopened image!", nullptr);

	return 0;
}

ETHER_API image_GetAlpha(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));

	Uint8 alpha;
	SDL_GetTextureAlphaMod(pImage->pTexture, &alpha);
	lua_pushnumber(L, alpha);

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

ETHER_API image_SetCurrentFrame(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	if (pImage->isDynamic)
	{
		pImage->currentFrame = lua_tonumber(L, 2);
		pImage->imageRect.x = (pImage->currentFrame % pImage->xAmount) * pImage->imageRect.w;
		pImage->imageRect.y = (pImage->currentFrame / pImage->xAmount) * pImage->imageRect.h;
	}
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Frame Failed", "You can't set frame for a static image", nullptr);

	return 0;
}

ETHER_API image_GetCurrentFrame(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	if (pImage->isDynamic)
		lua_pushnumber(L, pImage->currentFrame);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Get Frame Failed", "You can't get frame from a static image", nullptr);

	return 1;
}

ETHER_API image_SetAngle(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	double angle = lua_tonumber(L, 2);

	return 0;
}

ETHER_API image_GetAngle(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	lua_pushnumber(L, pImage->angle);

	return 1;
}

ETHER_API __gc_Image(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	delete pImage;

	return 0;
}