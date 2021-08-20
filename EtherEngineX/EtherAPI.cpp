#include "EtherAPI.h"

namespace EtherAPI {
	lua_State* pL = luaL_newstate();
	std::string strSceneName;

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

bool _LoadConfig()
{
	using namespace std;

	AdenJSONDocument _config;
	AdenJSONParseResult _result = _config.LoadFromFile("config.json");

	switch (_result.status)
	{
	case AdenJSONParseStatus::IOError:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Load Configuration Failed", _result.description.c_str(), nullptr);
		return false;
	case AdenJSONParseStatus::ParseError:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Parse Configuration Failed", _result.description.c_str(), nullptr);
		return false;
	default:
		break;
	}

	_config.ObjectForEach([&](const std::string& key, AdenJSONNode& node)-> bool 
		{
			if (key == "entry")
			{
				EtherAPI::strSceneName = node.GetStringValue();
				return true;
			}
			else if (key == "scene")
			{
				node.ArrayForEach([&](int idx, AdenJSONNode& scene)-> bool
					{
						scene[string("nextScene")].ArrayForEach([&](int idx, AdenJSONNode& nextScene)-> bool
							{
								_nextScene[scene[string("name")].GetStringValue()].push_back(nextScene.GetStringValue());
								return true;
							});
						return true;
					});
				return true;
			}
			else
				return false;
		});

	return true;
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
	bool ok = _LoadConfig();
	if (!ok) return 0;

	//注册全局函数
	lua_register(EtherAPI::pL, "GetVersion", getVersion);
	lua_register(EtherAPI::pL, "UsingModule", usingModule);
	lua_register(EtherAPI::pL, "CreateWindow", createWindow);

	int sceneIndex = 0;
	//在C++中为-1，而在lua中为0
	while (sceneIndex != -1)
	{
		int bRect = luaL_dofile(EtherAPI::pL, EtherAPI::strSceneName.c_str());
		if (bRect)
		{
			luaL_error(EtherAPI::pL, "An error occurred while trying to load %s", EtherAPI::strSceneName);
			return 0;
		}
		std::string moduleName = EtherAPI::strSceneName.substr(0, EtherAPI::strSceneName.size() - 4);

		lua_getglobal(EtherAPI::pL, moduleName.c_str());
		//调用init函数(没有返回值)
		lua_getfield(EtherAPI::pL, -1, "init");
		lua_pcall(EtherAPI::pL, 0, 0, 0);
		//调用update函数(返回值为下个场景索引)
		lua_getfield(EtherAPI::pL, -1, "update");
		lua_pcall(EtherAPI::pL, 0, 1, 0);
		sceneIndex = lua_tointeger(EtherAPI::pL, -1) - 1;
		lua_pop(EtherAPI::pL, 1);
		lua_getfield(EtherAPI::pL, -1, "unload");
		lua_pcall(EtherAPI::pL, 0, 0, 0);
		if (sceneIndex >= 0)
			EtherAPI::strSceneName = _nextScene[EtherAPI::strSceneName][sceneIndex];
	}
	lua_pop(EtherAPI::pL, 1);

	std::cin.get();
	//安全退出
	_HandleQuit();
	
	return 0;
}