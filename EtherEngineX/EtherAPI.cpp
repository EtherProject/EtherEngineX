#include "EtherAPI.h"

namespace EtherAPI {
	lua_State* pL = luaL_newstate();
	std::string strEntryName;

	SDL_Event event;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	const int WINDOW_FULLSCREEN =			1004;
	const int WINDOW_FULLSCREEN_DESKTOP =	1005;
	const int WINDOW_BORDERLESS =			1006;
	const int WINDOW_RESIZABLE =			1007;
	const int WINDOW_MAXIMIZED =			1008;
	const int WINDOW_MINIMIZED =			1009;
}

std::unordered_map<std::string, std::vector<std::string>> _nextScene;

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
	AdenJSONDocument _config;
	AdenJSONParseResult _result = _config.LoadFromFile("config.json");

	switch (_result.status)
	{
	case AdenJSONParseStatus::IOError:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Load Configuration Failed", _result.description.c_str(), nullptr);
		break;
	case AdenJSONParseStatus::ParseError:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Parse Configuration Failed", _result.description.c_str(), nullptr);
		break;
	default:
		break;
	}

	_config.ObjectForEach([&](const std::string& key, AdenJSONNode& node)-> bool 
		{
			if (key == "entry")
			{
				EtherAPI::strEntryName = node.GetStringValue();
				return true;
			}
			else if (key == "scene")
			{
				node.ArrayForEach([&](int idx, AdenJSONNode& node)-> bool 
					{

					});
				return true;
			}
			else
				return true;
		});

	return;
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
	using namespace EtherAPI;

	SDL_Rect rect;
	lua_getfield(L, 2, "x");
	rect.x = lua_tonumber(L, -1);
	lua_getfield(L, 2, "y");
	rect.y = lua_tonumber(L, -1);
	lua_getfield(L, 2, "w");
	rect.w = lua_tonumber(L, -1);
	lua_getfield(L, 2, "h");
	rect.h = lua_tonumber(L, -1);

	int flags = SDL_WINDOW_SHOWN;
	luaL_argcheck(L, lua_istable(L, 3), 3, "table expected");
	//第一个键nil
	lua_pushnil(L);

	while (lua_next(L, 3))
	{
		lua_pushvalue(L, -2);
		switch ((int)lua_tonumber(L, -2))
		{
		case WINDOW_FULLSCREEN:
			flags |= SDL_WINDOW_FULLSCREEN;
			break;
		case WINDOW_FULLSCREEN_DESKTOP:
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			break;
		case WINDOW_BORDERLESS:
			flags |= SDL_WINDOW_BORDERLESS;
			break;
		case WINDOW_RESIZABLE:
			flags |= SDL_WINDOW_RESIZABLE;
			break;
		case WINDOW_MAXIMIZED:
			flags |= SDL_WINDOW_MAXIMIZED;
			break;
		case WINDOW_MINIMIZED:
			flags |= SDL_WINDOW_MINIMIZED;
			break;
		default:
			luaL_error(L, "bad argument #3 to 'CreateWindow' (the elements of table must be MACRO number, got %s)", luaL_typename(L, -2));
			break;
		}
		lua_pop(L, 2);
	}

	window = SDL_CreateWindow(luaL_checkstring(L, 1), rect.x, rect.y, rect.w, rect.h, flags);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	return 0;
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
	lua_register(EtherAPI::pL, "UsingModule", usingModule);
	lua_register(EtherAPI::pL, "CreateWindow", createWindow);

	std::cin.get();

	//安全退出
	_HandleQuit();
	
	return 0;
}