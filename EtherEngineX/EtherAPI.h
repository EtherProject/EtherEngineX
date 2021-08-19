#ifndef _MAIN_H_
#define _MAIN_H_

#include "EtherMacros.h"
#include "EtherModule.h"
#include "AdenJSON.h"

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
void _LoadConfig();

ETHER_API getVersion(lua_State* L);
ETHER_API usingModule(lua_State* L);
ETHER_API createWindow(lua_State* L);

#endif // !_MAIN_H_