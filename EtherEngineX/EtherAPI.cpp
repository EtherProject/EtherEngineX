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
		std::cerr << "�ڳ��Լ���configʱ��������" << std::endl;

	// ���Գ���ʹ�� AdenJSON ��� cJSON �����˴������ļ�

	std::stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

}

std::unordered_map<std::string, std::function<EtherModule*()>> _mapMoudles = {

};

ETHER_API usingModule(lua_State* L)
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
	//SDL��ʼ��
	SDL_Init(SDL_INIT_EVERYTHING);
	//lua�������б�׼��
	luaL_openlibs(EtherAPI::pL);
	//��������������ֵ
	lua_gc(EtherAPI::pL, LUA_GCINC, 100);

	//��ȡ�����ļ�
	_LoadConfig();

	//ע��ȫ�ֺ���
	lua_register(EtherAPI::pL, "GetVersion", getVersion);

	luaL_dofile(EtherAPI::pL, "Main.lua");

	//��ȫ�˳�
	_HandleQuit();
	
	return 0;
}