#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "EtherGraphic.h"

class EtherSprite :public EtherNode
{
public:
	std::vector<EtherImage*> vImage;
};

class ModuleSprite : public EtherModule
{
public:
	static ModuleSprite& Instance();
	~ModuleSprite() {}
private:
	ModuleSprite();
};

ETHER_API CreateSprite(lua_State* L);

ETHER_API sprite_ChangeImage(lua_State* L);

ETHER_API sprite_AddImage(lua_State* L);

ETHER_API sprite_DeleteImage(lua_State* L);

ETHER_API __gc_Sprite(lua_State* L);

#endif // !_SPRITE_H_