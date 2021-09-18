#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "EtherModule.h"
#include "EtherUtils.h"

#include <SDL_mixer.h>

class ModuleMedia : public EtherModule
{
public:
	static ModuleMedia& Instance();
	~ModuleMedia() {}
private:
	ModuleMedia();
};

ETHER_API LoadMusic(lua_State* L);

ETHER_API CheckMusicPlaying(lua_State* L);

ETHER_API StopMusic(lua_State* L);

ETHER_API StopMusicWithFadeOut(lua_State* L);

ETHER_API SetPlayPosition(lua_State* L);

ETHER_API SetMusicVolumn(lua_State* L);

ETHER_API GetMusicVolumn(lua_State* L);

ETHER_API PauseMusic(lua_State* L);

ETHER_API ResumeMusic(lua_State* L);

ETHER_API RewindMusic(lua_State* L);

ETHER_API GetMusicFadingType(lua_State* L);

ETHER_API music_Play(lua_State* L);

ETHER_API music_PlayWithFadeIn(lua_State* L);

ETHER_API music_GetType(lua_State* L);

ETHER_API __gc_Music(lua_State* L);

ETHER_API LoadSoundFromFile(lua_State* L);

ETHER_API LoadSoundFromData(lua_State* L);

ETHER_API sound_Play(lua_State* L);

ETHER_API sound_SetVolumn(lua_State* L);

ETHER_API sound_GetVolumn(lua_State* L);

ETHER_API __gc_Sound(lua_State* L);

#endif // !_MEDIA_H_