#ifndef _MAIN_H_
#define _MAIN_H_

#include "EtherData.h"
#include "EtherMacros.h"

#include <lua.hpp>
#include <cJSON.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <sstream>

void _HandleQuit();

void _LoadConfig();

#endif // !_MAIN_H_