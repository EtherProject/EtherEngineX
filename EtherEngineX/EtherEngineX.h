#ifndef _ETHER_ENGINE_X_H_
#define _ETHER_ENGINE_X_H_

#include "AdenJSON.h"

#include "EtherGraphic.h"
#include "EtherWindow.h"
#include "EtherSprite.h"
#include "EtherAction.h"
#include "EtherEvent.h"
#include "EtherMedia.h"

#include <lua.hpp>
#include <cJSON.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <functional>

void _HandleQuit();
bool _LoadConfig();

ETHER_API GetVersion(lua_State* L);
ETHER_API UsingModule(lua_State* L);

#endif // !_ETHER_ENGINE_X_H_