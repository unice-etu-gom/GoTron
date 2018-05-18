#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

#include "TContext.h"



typedef enum EFxIdentifiers
{
    EFxKeyPress,
    EFxExplosion,
}   TFxIdentifier;

typedef enum EMusicIdentifiers
{
    EMusicMenu,
    EMusicGame,
}   TMusicIdentifier;

struct _SAudioContext
{
    Mix_Music*  p_music_game;
    Mix_Music*  p_music_menu;

    Mix_Chunk*  p_fx_explosion;
    Mix_Chunk*  p_fx_keypress;
};

typedef struct _SAudioContext*   TAudioContext;


//extern const char*  C_AUDIO_MUSIC_MENU;



int     audio_construct(TAudioContext* argContextPtr );
int     audio_destruct(TAudioContext* argContextPtr );


int     audio_playMusic( TAudioContext      argContextPtr,
                         TMusicIdentifier   argMusicID );
void    audio_stopMusic(void);

int     audio_playFx( TAudioContext argContextPtr,
                      TFxIdentifier argFxID );


#endif  /*< AUDIO_H */
