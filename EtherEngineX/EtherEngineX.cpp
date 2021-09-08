#include "EtherEngineX.h"

namespace EtherEngineX {
	lua_State* pLState = luaL_newstate();
	std::string strSceneName;

	SDL_Event event;

	const int QuitGame = -2;
	const int Continue = -1;
}

extern std::unordered_map<const char*, EtherWindow*> mapAllWindows;

std::unordered_map<std::string, std::vector<std::string>> _nextScene;

void _HandleQuit()
{
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
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
	{ "EtherWindow",[] {return &ModuleWindow::Instance(); }},
	{ "EtherImage", [] {return &ModuleImage::Instance(); }},
	{ "EtherNode", [] {return &ModuleNode::Instance(); } },
	{ "EtherSprite", [] {return &ModuleSprite::Instance(); }}
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

int main(int argc, char** argv)
{
	//SDL��ʼ��
	SDL_Init(SDL_INIT_EVERYTHING);
	//SDL���ÿ����
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
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
		//����Init����(û�з���ֵ)
		lua_getfield(EtherEngineX::pLState, -1, "Init");
		if (lua_pcall(EtherEngineX::pLState, 0, 0, 0))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Init", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -2; // �쳣����ֵ��ͬ��
		}

		//Update��������ֵ�����ж��Ƿ��˳��ó���,��������һ��������˭
		while (sceneIndex == EtherEngineX::Continue)
		{
			unsigned int timeFrameStart = SDL_GetTicks();

			//�¼���ȡ
			while (SDL_PollEvent(&EtherEngineX::event))
			{

			}

			//��������Ƴ���
			std::unordered_map<const char*, EtherWindow*>::iterator iterEnd = mapAllWindows.end();
			for (std::unordered_map<const char*, EtherWindow*>::iterator iter = mapAllWindows.begin(); iter != iterEnd; iter++)
			{
				std::vector<EtherLayer*> vCampLayer = (*iter).second->vLayer;
				for (std::vector<EtherLayer*>::iterator _iter = vCampLayer.begin(); _iter != vCampLayer.end(); _iter++)
				{
					SDL_RenderClear((*iter).second->pRenderer);
					(*_iter)->Draw();
					SDL_RenderPresent((*iter).second->pRenderer);
				}
			}

			//����Update����
			lua_getfield(EtherEngineX::pLState, -1, "Update");
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

		lua_getfield(EtherEngineX::pLState, -1, "Unload");
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