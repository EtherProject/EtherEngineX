#include "EtherAPI.h"

namespace EtherAPI {
	lua_State* pL = luaL_newstate();
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
	std::ifstream fin("config.json");
	if (!fin.good())
		std::cerr << "在尝试加载config时发生错误" << std::endl;

	// 可以尝试使用 AdenJSON 替代 cJSON 解析此处配置文件

	std::stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

}

std::unordered_map<std::string, std::function<EtherModule*()>> _mapMoudles = {

};

ETHER_API usingModule(lua_State* L)
{
	//寻找对应这个名字的Module
	auto iter = _mapMoudles.find(luaL_checkstring(L, 1));

	//如果找到了,则将该模块的所有数据推送到lua全局和交互栈中
	if (iter != _mapMoudles.end())
	{
		EtherModule* pModule = iter->second();
		pModule->PushMetaDataToGlobal(L);
		pModule->PushMoudleDataToStack(L);
	}
	//没找到则调用require函数获取本地模块
	else
	{
		lua_getglobal(EtherAPI::pL, "require");
		lua_pushstring(EtherAPI::pL, lua_tostring(L, 1));
		lua_call(EtherAPI::pL, 1, 1);
	}

	return 1;
}

ETHER_API getVersion(lua_State* L)
{
	lua_pushstring(L, _VERSION_);

	return 1;
}

ETHER_API createWindow(lua_State* L)
{
	SDL_Rect rect;
	lua_getfield(L, 2, "x");
	rect.x = lua_tonumber(L, -1);
	lua_getfield(L, 2, "y");
	rect.y = lua_tonumber(L, -1);
	lua_getfield(L, 2, "w");
	rect.w = lua_tonumber(L, -1);
	lua_getfield(L, 2, "h");
	rect.h = lua_tonumber(L, -1);


}

int main(int argc, char** argv)
{
	//SDL初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	//lua启动所有标准库
	luaL_openlibs(EtherAPI::pL);
	//设置垃圾回收数值
	lua_gc(EtherAPI::pL, LUA_GCINC, 100);

	//读取配置文件
	_LoadConfig();

	//注册全局函数
	lua_register(EtherAPI::pL, "GetVersion", getVersion);

	luaL_dofile(EtherAPI::pL, "Main.lua");

	//安全退出
	_HandleQuit();
	
	return 0;
}