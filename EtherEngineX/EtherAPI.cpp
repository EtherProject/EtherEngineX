#include"EtherAPI.h"

lua_State* pL = luaL_newstate();

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	luaL_openlibs(pL);
	return 0;
}