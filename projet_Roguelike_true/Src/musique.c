#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

int lire_musique(const char *MUSIC) {
    int result = 0;
    int flags = MIX_INIT_MP3;

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS(MUSIC);
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
    }
    Mix_PlayMusic(music, 1);



    Mix_FreeMusic(music);
    return 0;
}
