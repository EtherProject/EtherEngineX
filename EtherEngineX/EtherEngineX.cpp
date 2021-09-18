#include "EtherEngineX.h"

namespace EtherEngineX {
	lua_State* pLState = luaL_newstate();
	std::string strSceneName;

	const int QuitGame = -2;
	const int Continue = -1;
}

//窗口管理
extern std::unordered_map<const char*, EtherWindow*> mapAllWindows;

//动作管理
extern std::vector<EtherNodeAction*> vAction;

//事件管理
extern EtherListenerManager listenerManager;

//场景管理
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
	{ "EtherSprite", [] {return &ModuleSprite::Instance(); }},
	{ "EtherAction", [] {return &ModuleAction::Instance(); }},
	{ "EtherEvent", [] {return &ModuleEvent::Instance(); }}
};

ETHER_API UsingModule(lua_State* L)
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

ETHER_API GetVersion(lua_State* L)
{
	lua_pushstring(L, _VERSION_);

	return 1;
}

int main(int argc, char** argv)
{
	//SDL初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	//SDL设置抗锯齿
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	//lua启动所有标准库
	luaL_openlibs(EtherEngineX::pLState);
	//设置垃圾回收数值
	lua_gc(EtherEngineX::pLState, LUA_GCINC, 200);

	//读取配置文件
	bool ok = _LoadConfig();
	if (!ok) return 0;

	//注册全局函数
	lua_register(EtherEngineX::pLState, "GetVersion", GetVersion);
	lua_register(EtherEngineX::pLState, "UsingModule", UsingModule);

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
		//调用Init函数(没有返回值)
		lua_getfield(EtherEngineX::pLState, -1, "Init");
		if (lua_pcall(EtherEngineX::pLState, 0, 0, 0))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Init", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -2; // 异常返回值，同上
		}

		//Update函数返回值用于判断是否退出该场景,并决定下一个场景是谁
		while (sceneIndex == EtherEngineX::Continue)
		{
			unsigned int timeFrameStart = SDL_GetTicks();

			//监听者管理(处理事件)
			while (SDL_PollEvent(&listenerManager.event))
			{
				switch (listenerManager.event.type)
				{
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEWHEEL:
					listenerManager.currentType = EVENT_TYPE::MOUSE;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					listenerManager.currentType = EVENT_TYPE::KEYBOARD;
					break;
				case SDL_WINDOWEVENT:
					listenerManager.currentType = EVENT_TYPE::WINDOW;
				}

				for (auto iter = listenerManager.mapListener.begin(); iter != listenerManager.mapListener.end(); iter++)
				{
					if (listenerManager.currentType == (*iter).second->type)
					{
						if (listenerManager.currentType == EVENT_TYPE::MOUSE)
							(*iter).second->mouse.Callback(EtherEngineX::pLState, &listenerManager.event);
						else if (listenerManager.currentType == EVENT_TYPE::KEYBOARD)
							(*iter).second->keyboard.Callback(EtherEngineX::pLState, &listenerManager.event);
						else if (listenerManager.currentType == EVENT_TYPE::WINDOW)
							(*iter).second->window.Callback(EtherEngineX::pLState, &listenerManager.event);
					}
				}
			}

			//检测动作管理向量中有没有需要删除的动作
			for (int index = vAction.size() - 1; index >= 0; index--)
			{
				std::vector<EtherNodeAction*>::iterator iter = vAction.begin() + index;
				if ((*iter)->isDone)
				{
					delete vAction[index];
					vAction.erase(iter);
				}
			}

			//运行动作管理向量中的所有动作
			for (std::vector<EtherNodeAction*>::iterator iter = vAction.begin(); iter != vAction.end(); iter++)
			{
				EtherNode* pNode = (*iter)->pNode;
				if (pNode->isRuning)
				{
					std::vector<EtherAction*>::iterator iterA = (*iter)->vAction.begin() + (*iter)->index;
					std::vector<std::function<void(EtherNode*, EtherAction*)> >::iterator iterNA = (*iter)->vNodeAction.begin() + (*iter)->index;
					std::vector<EtherAction*>::iterator iterEnd = (*iter)->vAction.end();

					if (iterA != iterEnd)
					{
						if ((*iterA)->progress < (*iterA)->last)
						{
							(*iterNA)(pNode, (*iterA));
							(*iterA)->progress++;
						}
						else
						{
							(*iterA)->progress = 0;
							if ((*iterA)->callBack != LUA_REFNIL)
							{
								lua_rawgeti(EtherEngineX::pLState, LUA_REGISTRYINDEX, (*iterA)->callBack);
								lua_pcall(EtherEngineX::pLState, 0, 0, 0);
							}
							(*iter)->index++;
						}
					}
					else
						(*iter)->isDone = true;
				}
			}

			//调用Update函数
			lua_getfield(EtherEngineX::pLState, -1, "Update");
			if (lua_pcall(EtherEngineX::pLState, 0, 1, 0))
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Update", lua_tostring(EtherEngineX::pLState, -1), nullptr);
				return -3; // 异常返回值，同上
			}
			sceneIndex = lua_tointeger(EtherEngineX::pLState, -1) - 1;
			lua_pop(EtherEngineX::pLState, 1);

			//将画面绘制出来
			for (auto iter = mapAllWindows.begin(); iter != mapAllWindows.end(); iter++)
				for (auto _iter = (*iter).second->vNode.begin(); _iter != (*iter).second->vNode.end(); _iter++)
				{
					SDL_RenderClear((*iter).second->pRenderer);
					(*_iter)->Draw();
					SDL_RenderPresent((*iter).second->pRenderer);
				}

			//延时,保证游戏帧数
			unsigned int timeFrameEnd = SDL_GetTicks();
			if (timeFrameEnd - timeFrameStart < 1000 / ETHER_FRAME)
				SDL_Delay(1000 / ETHER_FRAME - (timeFrameEnd - timeFrameStart));
		}

		lua_getfield(EtherEngineX::pLState, -1, "Unload");
		if (lua_pcall(EtherEngineX::pLState, 0, 0, 0))
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Unload", lua_tostring(EtherEngineX::pLState, -1), nullptr);
			return -4; // 异常返回值，同上
		}
		if (sceneIndex >= 0 && sceneIndex < _nextScene[EtherEngineX::strSceneName].size())
			EtherEngineX::strSceneName = _nextScene[EtherEngineX::strSceneName][sceneIndex];
	}
	lua_pop(EtherEngineX::pLState, 1);

	//安全退出
	_HandleQuit();
	
	return 0;
}