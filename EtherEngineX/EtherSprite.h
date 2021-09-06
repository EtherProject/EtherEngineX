#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "EtherImage.h"

class EtherSprite
{
public:
	unsigned int curretImage;
	std::vector<EtherImage*> vImage;

};

class ModuleSprite : public EtherModule
{

};

#endif // !_SPRITE_H_