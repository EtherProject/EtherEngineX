#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "EtherNode.h"
#include "EtherModule.h"

#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class EtherImage: public EtherNode
{
public:
	enum class LoadType
	{
		fromFile = 0,
		fromData = 1
	};

	bool isRotated;
	bool isReshaped;
	bool isDynamic;
	LoadType type;

	SDL_Surface* pSurface;
	SDL_Texture* pTexture;
	SDL_Rect imageRect;
};

class ModuleImage : public EtherModule
{
public:
	static ModuleImage& Instance();
	~ModuleImage() {}
private:
	ModuleImage();
};

#endif // !_IMAGE_H_