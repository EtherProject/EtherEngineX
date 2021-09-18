#include "EtherMedia.h"

ModuleMedia& ModuleMedia::Instance()
{
	static ModuleMedia* _instance = new ModuleMedia();
	return *_instance;
}

ModuleMedia::ModuleMedia()
{
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	_vCMethods =
	{
		{"LoadMusic", LoadMusic},
		{"LoadSoundFromFile", LoadSoundFromFile},
		{"LoadSoundFromData", LoadSoundFromData},
		{"StopMusic", StopMusic},
		{"StopMusicWithFadeOut", StopMusicWithFadeOut},
		{"SetPlayPosition", SetPlayPosition},
		{"GetMusicVolumn", GetMusicVolumn},
		{"SetMusicVolumn", SetMusicVolumn},
		{"CheckMusicPlaying", CheckMusicPlaying},
		{"GetMusicFadingType", GetMusicFadingType},
		{"PauseMusic", PauseMusic},
		{"ResumeMusic", ResumeMusic},
		{"RewindMusic", RewindMusic}
	};

	_vMacros =
	{
		//淡入淡出
		{"FADING_NONE", MIX_NO_FADING},
		{"FADING_OUT", MIX_FADING_OUT},
		{"FADING_IN", MIX_FADING_IN},

		//音乐类型
		{"TYPE_WAV", MUS_WAV},
		{"TYPE_MP3", MUS_MP3},
		{"TYPE_OGG", MUS_OGG},
		{"TYPE_CMD", MUS_CMD},
		{"TYPE_MOD", MUS_MOD},
		{"TYPE_MID", MUS_MID},
		{"TYPE_NONE", MUS_NONE}
	};

	_vMetaData =
	{
		{
			"EtherMusic",
			nullptr,
			{
				{"Play", music_Play},
				{"PlayWithFadeIn", music_PlayWithFadeIn},
				{"GetType", music_GetType}
			},
			__gc_Music
		},
		{
			"EtherSound",
			nullptr,
			{
				{"Play", sound_Play},
				{"GetVolumn", sound_GetVolumn},
				{"SetVolumn", sound_SetVolumn}
			},
			__gc_Sound
		}
	};
}

ETHER_API LoadMusic(lua_State* L)
{
	Mix_Music* pMusic = Mix_LoadMUS(luaL_checkstring(L, 1));
	luaL_argcheck(L, pMusic, 1, "load music failed");

	Mix_Music** uppMusic = (Mix_Music**)lua_newuserdata(L, sizeof(Mix_Music*));
	*uppMusic = pMusic;
	luaL_getmetatable(L, "EtherMusic");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API GetMusicFadingType(lua_State* L)
{
	switch (Mix_FadingMusic())
	{
	case MIX_NO_FADING:
		lua_pushinteger(L, MIX_NO_FADING);
		break;
	case MIX_FADING_OUT:
		lua_pushinteger(L, MIX_FADING_OUT);
		break;
	case MIX_FADING_IN:
		lua_pushinteger(L, MIX_FADING_IN);
		break;
	default:
		break;
	}
	return 1;
}

ETHER_API CheckMusicPlaying(lua_State* L)
{
	lua_pushboolean(L, Mix_PlayingMusic());

	return 1;
}

ETHER_API StopMusic(lua_State* L)
{
	Mix_HaltMusic();

	return 0;
}

ETHER_API StopMusicWithFadeOut(lua_State* L)
{
	Mix_FadeOutMusic(luaL_checknumber(L, 1));

	return 0;
}

ETHER_API SetPlayPosition(lua_State* L)
{
	Mix_SetMusicPosition(luaL_checknumber(L, 1));

	return 0;
}

ETHER_API SetMusicVolumn(lua_State* L)
{
	Mix_VolumeMusic(luaL_checknumber(L, 1));

	return 0;
}

ETHER_API GetMusicVolumn(lua_State* L)
{
	lua_pushnumber(L, Mix_VolumeMusic(-1));

	return 1;
}

ETHER_API music_Play(lua_State* L)
{
	Mix_Music* pMusic = (Mix_Music*)(*(void**)luaL_checkudata(L, 1, "EtherMusic"));
	luaL_argcheck(L, pMusic, 1, "get music failed");
	Mix_PlayMusic(pMusic, luaL_checknumber(L, 2));

	return 0;
}

ETHER_API music_PlayWithFadeIn(lua_State* L)
{
	Mix_Music* pMusic = (Mix_Music*)(*(void**)luaL_checkudata(L, 1, "EtherMusic"));
	luaL_argcheck(L, pMusic, 1, "get music failed");
	Mix_FadeInMusic(pMusic, luaL_checknumber(L, 2), luaL_checknumber(L, 3));

	return 0;
}

ETHER_API music_GetType(lua_State* L)
{
	Mix_Music* pMusic = (Mix_Music*)(*(void**)luaL_checkudata(L, 1, "EtherMusic"));
	luaL_argcheck(L, pMusic, 1, "get music failed");

	switch (Mix_GetMusicType(pMusic))
	{
	case MUS_WAV:
		lua_pushnumber(L, MUS_WAV);
		break;
	case MUS_MP3:
		lua_pushnumber(L, MUS_MP3);
		break;
	case MUS_OGG:
		lua_pushnumber(L, MUS_OGG);
		break;
	case MUS_CMD:
		lua_pushnumber(L, MUS_CMD);
		break;
	case MUS_MOD:
		lua_pushnumber(L, MUS_MOD);
		break;
	case MUS_MID:
		lua_pushnumber(L, MUS_MID);
		break;
	default:
		lua_pushnumber(L, MUS_NONE);
		break;
	}

	return 1;
}

ETHER_API PauseMusic(lua_State* L)
{
	Mix_PauseMusic();

	return 0;
}

ETHER_API ResumeMusic(lua_State* L)
{
	Mix_ResumeMusic();

	return 0;
}

ETHER_API RewindMusic(lua_State* L)
{
	Mix_RewindMusic();

	return 0;
}

ETHER_API __gc_Music(lua_State* L)
{
	Mix_Music* pMusic = (Mix_Music*)(*(void**)luaL_checkudata(L, 1, "EtherMusic"));
	luaL_argcheck(L, pMusic, 1, "load music failed");

	Mix_FreeMusic(pMusic);
	pMusic = nullptr;

	return 0;
}

ETHER_API LoadSoundFromFile(lua_State* L)
{
	Mix_Chunk* sound = Mix_LoadWAV(luaL_checkstring(L, 1));
	luaL_argcheck(L, sound, 1, "load sound failed");

	Mix_Chunk** uppSound = (Mix_Chunk**)lua_newuserdata(L, sizeof(Mix_Chunk*));
	*uppSound = sound;
	luaL_getmetatable(L, "EtherSound");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API LoadSoundFromData(lua_State* L)
{
	size_t size = 0;
	Mix_Chunk* sound = Mix_LoadWAV_RW(SDL_RWFromMem((void*)luaL_checklstring(L, 1, &size), size), 1);
	luaL_argcheck(L, sound, 1, "load sound failed");

	Mix_Chunk** uppSound = (Mix_Chunk**)lua_newuserdata(L, sizeof(Mix_Chunk*));
	*uppSound = sound;
	luaL_getmetatable(L, "EtherSound");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API sound_Play(lua_State* L)
{
	Mix_Chunk* pSound = (Mix_Chunk*)(*(void**)luaL_checkudata(L, 1, "EtherSound"));
	luaL_argcheck(L, pSound, 1, "load soud failed");

	Mix_PlayChannel(-1, pSound, luaL_checknumber(L, 2));

	return 0;
}

ETHER_API sound_SetVolumn(lua_State* L)
{
	Mix_Chunk* pSound = (Mix_Chunk*)(*(void**)luaL_checkudata(L, 1, "EtherSound"));
	luaL_argcheck(L, pSound, 1, "load soud failed");

	Mix_VolumeChunk(pSound, luaL_checknumber(L, 2));

	return 0;
}

ETHER_API sound_GetVolumn(lua_State* L)
{
	Mix_Chunk* pSound = (Mix_Chunk*)(*(void**)luaL_checkudata(L, 1, "EtherSound"));
	luaL_argcheck(L, pSound, 1, "load soud failed");

	lua_tonumber(L, pSound->volume);

	return 1;
}

ETHER_API __gc_Sound(lua_State* L)
{
	Mix_Chunk* pSound = (Mix_Chunk*)(*(void**)luaL_checkudata(L, 1, "EtherSound"));
	luaL_argcheck(L, pSound, 1, "load music failed");

	Mix_FreeChunk(pSound);
	pSound = nullptr;

	return 0;
}