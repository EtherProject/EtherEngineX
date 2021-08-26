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
	{ "EtherNode", [] {return &ModuleNode::Instance(); } }
};

ETHER_API UsingModule(lua_State* L)
{
	//Ѱ�Ҷ�Ӧ������ֵ�Module
	auto iter = _mapMoudles.find(luaL_checkstring(L, 1));

	//����ҵ���,�򽫸�ģ��������������͵�luaȫ�ֺͽ���ջ��
	if (iter != _mapMoudles.end())
	{
		EtherModule* pModule = iter->second();
		pModule->PushMetaDataToGlobal(L);
		pModule->PushMoudleDataToStack(L);
	}
	//û�ҵ������require������ȡ����ģ��
	else
	{
		lua_getglobal(EtherEngineX::pLState, "require");
		lua_pushstring(EtherEngineX::pLState, lua_tostring(L, 1));
		lua_call(EtherEngineX::pLState, 1, 1);
	}

	return 1;
}

ETHER_API GetVersion(lua_State* L)
{
	lua_pushstring(L, _VERSION_);

	return 1;
}

ETHER_API CreateWindow(lua_State* L)
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
	//��һ����nil
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
	//SDL��ʼ��
	SDL_Init(SDL_INIT_EVERYTHING);
	//lua�������б�׼��
	luaL_openlibs(EtherEngineX::pLState);
	//��������������ֵ
	lua_gc(EtherEngineX::pLState, LUA_GCINC, 100);

	//��ȡ�����ļ�
	bool ok = _LoadConfig();
	if (!ok) return 0;

	//ע��ȫ�ֺ���
	lua_register(EtherEngineX::pLState, "GetVersion", GetVersion);
	lua_register(EtherEngineX::pLState, "UsingModule", UsingModule);
	lua_register(EtherEngineX::pLState, "CreateWindow", CreateWindow);

	int sceneIndex = EtherEngineX::Continue;
	//��C++��Ϊ-2������lua��Ϊ-1
	while (sceneIndex != EtherEngineX::QuitGame)
	{
		sceneIndex = EtherEngineX::Continue;
		if (luaL_dofile(EtherEngineX::pLState, EtherEngineX::strSceneName.c_str()))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Load File Failed", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -1;	// �쳣����ֵ���������Զ����������ֵ
		}
		std::string moduleName = EtherEngineX::strSceneName.substr(0, EtherEngineX::strSceneName.size() - 4);

		lua_getglobal(EtherEngineX::pLState, moduleName.c_str());
		//����init����(û�з���ֵ)
		lua_getfield(EtherEngineX::pLState, -1, "init");
		if (lua_pcall(EtherEngineX::pLState, 0, 0, 0))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Init", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -2; // �쳣����ֵ��ͬ��
		}

		//����update����(����ֵΪ�¸���������)
		while (sceneIndex == EtherEngineX::Continue)
		{
			unsigned int timeFrameStart = SDL_GetTicks();
			lua_getfield(EtherEngineX::pLState, -1, "update");
			if (lua_pcall(EtherEngineX::pLState, 0, 1, 0))
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Update", lua_tostring(EtherEngineX::pLState, -1), nullptr);
				return -3; // �쳣����ֵ��ͬ��
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
			return -4; // �쳣����ֵ��ͬ��
		}
		if (sceneIndex >= 0 && sceneIndex < _nextScene[EtherEngineX::strSceneName].size())
			EtherEngineX::strSceneName = _nextScene[EtherEngineX::strSceneName][sceneIndex];
	}
	lua_pop(EtherEngineX::pLState, 1);

	std::cin.get();
	//��ȫ�˳�
	_HandleQuit();
	
	return 0;
}