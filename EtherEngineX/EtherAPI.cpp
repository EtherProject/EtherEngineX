#include "EtherAPI.h"

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
		cerr << "�ڳ��Լ���configʱ��������" << endl;

	stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

}

int main(int argc, char** argv)
{
	//SDL��ʼ��
	SDL_Init(SDL_INIT_EVERYTHING);
	//lua�������б�׼��
	luaL_openlibs(pL);
	//��������������ֵ
	lua_gc(pL, LUA_GCINC, 100);

	//��ȡ�����ļ�
	_LoadConfig();

	//��ȫ�˳�
	_HandleQuit();
	return 0;
}