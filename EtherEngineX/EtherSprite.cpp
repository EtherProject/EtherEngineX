#include "EtherSprite.h"

ModuleSprite& ModuleSprite::Instance()
{
	static ModuleSprite* _instance = new ModuleSprite();
	return *_instance;
}

ModuleSprite::ModuleSprite()
{
	_vCMethods =
	{
		{"CreateSprite", CreateSprite}
	};

	_vMetaData =
	{
		{
			"EtherSprite",
			"EtherNode",
			{
				{"ChangeImage", sprite_ChangeImage},
				{"AddImage", sprite_AddImage},
				{"DeleteImage", sprite_DeleteImage}
			},
			__gc_Sprite
		}
	};
}

ETHER_API CreateSprite(lua_State* L)
{
	EtherSprite* pSprite = new EtherSprite();
	EtherSprite** uppSprite = (EtherSprite**)lua_newuserdata(L, sizeof(EtherSprite*));
	*uppSprite = pSprite;
	luaL_getmetatable(L, "EtherSprite");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API sprite_ChangeImage(lua_State* L)
{
	EtherSprite* pSprite = (EtherSprite*)(*(void**)luaL_checkudata(L, 1, "EtherSprite"));
	unsigned int index = lua_tonumber(L, 2) - 1;

	pSprite->pImage = pSprite->vImage[index];

	return 0;
}

ETHER_API sprite_AddImage(lua_State* L)
{
	EtherSprite* pSprite = (EtherSprite*)(*(void**)luaL_checkudata(L, 1, "EtherSprite"));
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));

	if (!pImage->isOpened)
	{
		pImage->pTexture = SDL_CreateTextureFromSurface(pSprite->pRenderer, pImage->pSurface);
		pImage->isOpened = true;
	}

	pSprite->vImage.push_back(pImage);

	return 0;
}

ETHER_API sprite_DeleteImage(lua_State* L)
{
	using namespace std;
	EtherSprite* pSprite = (EtherSprite*)(*(void**)luaL_checkudata(L, 1, "EtherSprite"));
	unsigned int index = lua_tonumber(L, 2) - 1;

	SDL_DestroyTexture(pSprite->vImage[index]->pTexture);

	vector<EtherImage*>::iterator iter = pSprite->vImage.begin() + index;
	pSprite->vImage.erase(iter);

	return 0;
}

ETHER_API __gc_Sprite(lua_State* L)
{
	EtherSprite* pSprite = (EtherSprite*)(*(void**)luaL_checkudata(L, 1, "EtherSprite"));
	delete pSprite;

	return 0;
}