#include "EtherEngineX.h"

namespace EtherEngineX {
	lua_State* pLState = luaL_newstate();
	std::string strSceneName;

	SDL_Event event;
	SDL_Window* pWindow = nullptr;
	SDL_Renderer* pWRenderer = nullptr;

	enum class WINDOW
	{
		FULLSCREEN = 1004,
		FULLSCREEN_DESKTOP = 1005,
		BORDERLESS = 1006,
		RESIZABLE = 1007,
		MAXIMIZED = 1008,
		MINIMIZED = 1009
	};

	const int QuitGame = -2;
	const int Continue = -1;
}

std::unordered_map<std::string, std::vector<std::string>> _nextScene;

void _HandleQuit()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();

	SDL_DestroyRenderer(EtherEngineX::pWRenderer);
	EtherEngineX::pWRenderer = nullptr;

	if (EtherEngineX::pWindow)
	{
		SDL_DestroyWindow(EtherEngineX::pWindow);
		EtherEngineX::pWindow = nullptr;
	}

	SDL_Quit();
}

bool _LoadConfig()
{
	using namespace std;

	AdenJSONDocument jsonDoc;
	AdenJSONParseResult resJSONParse = jsonDoc.LoadFromFile("config.json");

	switch (resJSONParse.status)
	{
	case AdenJSONParseStatus::IOError:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Open Configuration File Failed", resJSONParse.description.c_str(), nullptr);
		return false;
	case AdenJSONParseStatus::ParseError:
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Parse Configuration Failed", resJSONParse.description.c_str(), nullptr);
		return false;
	default:
		break;
	}

	jsonDoc.ObjectForEach([&](const std::string& key, AdenJSONNode& node)-> bool 
		{
			if (key == "entry")
			{
				EtherEngineX::strSceneName = node.GetStringValue();
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
		lua_getglobal(EtherEngineX::pLState, "require");
		lua_pushstring(EtherEngineX::pLState, lua_tostring(L, 1));
		lua_call(EtherEngineX::pLState, 1, 1);
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
	SDL_Rect rcWindow;
	lua_getfield(L, 2, "x");
	rcWindow.x = lua_tonumber(L, -1);
	lua_getfield(L, 2, "y");
	rcWindow.y = lua_tonumber(L, -1);
	lua_getfield(L, 2, "w");
	rcWindow.w = lua_tonumber(L, -1);
	lua_getfield(L, 2, "h");
	rcWindow.h = lua_tonumber(L, -1);

	int flags = SDL_WINDOW_SHOWN;
	luaL_argcheck(L, lua_istable(L, 3), 3, "table expected");
	//第一个键nil
	lua_pushnil(L);

	while (lua_next(L, 3))
	{
		lua_pushvalue(L, -2);
		switch ((int)lua_tonumber(L, -2))
		{
		case (int)EtherEngineX::WINDOW::FULLSCREEN:
			flags |= SDL_WINDOW_FULLSCREEN;
			break;
		case (int)EtherEngineX::WINDOW::FULLSCREEN_DESKTOP:
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			break;
		case (int)EtherEngineX::WINDOW::BORDERLESS:
			flags |= SDL_WINDOW_BORDERLESS;
			break;
		case (int)EtherEngineX::WINDOW::RESIZABLE:
			flags |= SDL_WINDOW_RESIZABLE;
			break;
		case (int)EtherEngineX::WINDOW::MAXIMIZED:
			flags |= SDL_WINDOW_MAXIMIZED;
			break;
		case (int)EtherEngineX::WINDOW::MINIMIZED:
			flags |= SDL_WINDOW_MINIMIZED;
			break;
		default:
			luaL_error(L, "bad argument #3 to 'CreateWindow' (the elements of table must be MACRO number, got %s)", luaL_typename(L, -2));
			break;
		}
		lua_pop(L, 2);
	}

	EtherEngineX::pWindow = SDL_CreateWindow(luaL_checkstring(L, 1), rcWindow.x, rcWindow.y, rcWindow.w, rcWindow.h, flags);
	EtherEngineX::pWRenderer = SDL_CreateRenderer(EtherEngineX::pWindow, -1, SDL_RENDERER_ACCELERATED);

	return 0;
}

int main(int argc, char** argv)
{
	//SDL初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	//lua启动所有标准库
	luaL_openlibs(EtherEngineX::pLState);
	//设置垃圾回收数值
	lua_gc(EtherEngineX::pLState, LUA_GCINC, 100);

	//读取配置文件
	bool ok = _LoadConfig();
	if (!ok) return 0;

	//注册全局函数
	lua_register(EtherEngineX::pLState, "GetVersion", getVersion);
	lua_register(EtherEngineX::pLState, "UsingModule", usingModule);
	lua_register(EtherEngineX::pLState, "CreateWindow", createWindow);

	int sceneIndex = EtherEngineX::Continue;
	//在C++中为-2，而在lua中为-1
	while (sceneIndex != EtherEngineX::QuitGame)
	{
		sceneIndex = EtherEngineX::Continue;
		if (luaL_dofile(EtherEngineX::pLState, EtherEngineX::strSceneName.c_str()))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Load File Failed", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -1;	// 异常返回值，后续可以定义有意义的值
		}
		std::string moduleName = EtherEngineX::strSceneName.substr(0, EtherEngineX::strSceneName.size() - 4);

		lua_getglobal(EtherEngineX::pLState, moduleName.c_str());
		//调用init函数(没有返回值)
		lua_getfield(EtherEngineX::pLState, -1, "init");
		if (lua_pcall(EtherEngineX::pLState, 0, 0, 0))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Init", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -2; // 异常返回值，同上
		}

		//调用update函数(返回值为下个场景索引)
		while (sceneIndex == EtherEngineX::Continue)
		{
			unsigned int timeFrameStart = SDL_GetTicks();
			lua_getfield(EtherEngineX::pLState, -1, "update");
			if (lua_pcall(EtherEngineX::pLState, 0, 1, 0))
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Update", lua_tostring(EtherEngineX::pLState, -1), nullptr);
				return -3; // 异常返回值，同上
			}
			sceneIndex = lua_tointeger(EtherEngineX::pLState, -1) - 1;
			lua_pop(EtherEngineX::pLState, 1);
			unsigned int timeFrameEnd = SDL_GetTicks();
			if (timeFrameEnd - timeFrameStart < 1000 / 60)
				SDL_Delay(1000 / 60 - (timeFrameEnd - timeFrameStart));
		}

		lua_getfield(EtherEngineX::pLState, -1, "unload");
		if (lua_pcall(EtherEngineX::pLState, 0, 0, 0))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Unload", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -4; // 异常返回值，同上
		}
		if (sceneIndex >= 0 && sceneIndex < _nextScene[EtherEngineX::strSceneName].size())
			EtherEngineX::strSceneName = _nextScene[EtherEngineX::strSceneName][sceneIndex];
	}
	lua_pop(EtherEngineX::pLState, 1);

	std::cin.get();
	//安全退出
	_HandleQuit();
	
	return 0;
}