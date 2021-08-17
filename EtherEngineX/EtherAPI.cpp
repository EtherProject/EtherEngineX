#include "EtherAPI.h"
using namespace std;

lua_State* pL = luaL_newstate();

namespace EtherAPI {
	SDL_Event event;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
}

void _HandleQuit()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();

	SDL_DestroyRenderer(EtherAPI::renderer);
	EtherAPI::renderer = nullptr;

	if (EtherAPI::window)
	{
		SDL_DestroyWindow(EtherAPI::window);
		EtherAPI::window = nullptr;
	}

	SDL_Quit();
}

void _LoadConfig()
{
	using namespace std;
	ifstream fin("config.json");
	if (!fin.good())
		cerr << "在尝试加载config时发生错误" << endl;

	stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

}

ETHER_API getVersion(lua_State* L)
{
	lua_pushstring(L, _VERSION_);

	return 1;
}

int main(int argc, char** argv)
{
	//SDL初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	//lua启动所有标准库
	luaL_openlibs(pL);
	//设置垃圾回收数值
	lua_gc(pL, LUA_GCINC, 100);

	//读取配置文件
	_LoadConfig();

	//注册全局函数
	lua_register(pL, "GetVersion", getVersion);

	luaL_dofile(pL, "Main.lua");

	//安全退出
	_HandleQuit();
	
	return 0;
}