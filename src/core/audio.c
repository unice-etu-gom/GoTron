#include "audio.h"

#include <SDL_mixer.h>

#include "core/macros.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "core", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "core", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

const char* C_AUDIO_FX_EXPLOSION    = "rsrc/audio/fx/explosion01.wav";
const char* C_AUDIO_FX_KEYPRESS     = "rsrc/audio/fx/accent01.wav";
const char* C_AUDIO_MUSIC_MENU      = "rsrc/audio/music/menu.wav";
const char* C_AUDIO_MUSIC_GAME      = "rsrc/audio/music/game.wav";

/* ########################################################################## */
/* ########################################################################## */

int audio_construct(TAudioContext* argContextPtr)
{
    int retVal  = EXIT_SUCCESS;


    (*argContextPtr)    = malloc( sizeof( struct _SAudioContext ) );
    (*argContextPtr)->p_fx_explosion    = NULL;
    (*argContextPtr)->p_fx_keypress     = NULL;
    (*argContextPtr)->p_music_game      = NULL;
    (*argContextPtr)->p_music_menu      = NULL;


    if( Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 1, 2048) != 0 )
    {
        TRACE_ERR( "An error occured while initializing Audio interface !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ((*argContextPtr)->p_music_game=Mix_LoadMUS( C_AUDIO_MUSIC_GAME ))
             == NULL )
    {
        TRACE_ERR( "An error occured while loading music_game !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ((*argContextPtr)->p_music_menu=Mix_LoadMUS( C_AUDIO_MUSIC_MENU ))
             == NULL )
    {
        TRACE_ERR( "An error occured while loading music_menu !" );
        retVal  = EXIT_FAILURE;
    }


    else if(((*argContextPtr)->p_fx_explosion=Mix_LoadWAV(C_AUDIO_FX_EXPLOSION))
             == NULL )
    {
        TRACE_ERR( "An error occured while loading fx_explosion !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ((*argContextPtr)->p_fx_keypress=Mix_LoadWAV(C_AUDIO_FX_KEYPRESS))
             == NULL )
    {
        TRACE_ERR( "An error occured while loading fx_keypress !" );
        retVal  = EXIT_FAILURE;
    }



    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int audio_destruct(TAudioContext* argContextPtr)
{
    int retVal  = EXIT_SUCCESS;


    Mix_Quit();

    Mix_FreeChunk( (*argContextPtr)->p_fx_explosion );
    Mix_FreeChunk( (*argContextPtr)->p_fx_keypress );
    Mix_FreeMusic( (*argContextPtr)->p_music_game );
    Mix_FreeMusic( (*argContextPtr)->p_music_menu );

    FREE( (*argContextPtr) );

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int audio_playMusic( TAudioContext      argContextPtr,
                     TMusicIdentifier   argMusicID )
{
    Mix_Music*  p_music     = NULL;
    int         retVal      = EXIT_SUCCESS;


    switch( argMusicID )
    {
        case EMusicGame:
            p_music = argContextPtr->p_music_game;
            break;


        case EMusicMenu:
            p_music = argContextPtr->p_music_menu;
            break;


        default:
            TRACE_ERR( "Unknown music with ID '%d' !",
                       argMusicID );
            break;
    }


    if( p_music == NULL )
    {
        TRACE_ERR( "Can't play music !" );
        retVal  = EXIT_FAILURE;
    }
    else if( Mix_PlayMusic( p_music, -1 ) < 0 )
    {
        TRACE_ERR( "An error occured while stating music !" );
        retVal  = EXIT_FAILURE;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int audio_playFx(TAudioContext argContextPtr, TFxIdentifier argFxID)
{
    Mix_Chunk*  p_chunk     = NULL;
    int         retVal      = EXIT_SUCCESS;


    switch( argFxID )
    {
        case EFxExplosion:
            p_chunk = argContextPtr->p_fx_explosion;
            break;


        case EFxKeyPress:
            p_chunk = argContextPtr->p_fx_keypress;
            break;


        default:
            TRACE_ERR( "Unknown fx with ID '%d' !",
                       argFxID );
            break;
    }


    if( p_chunk == NULL )
    {
        TRACE_ERR( "Can't play fx !" );
        retVal  = EXIT_FAILURE;
    }
    else if( Mix_PlayChannel( -1, p_chunk, 0 ) < 0 )
    {
        TRACE_ERR( "An error occured while stating fx !" );
        retVal  = EXIT_FAILURE;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    audio_stopMusic(void)
{
    Mix_HaltMusic();
}

/* ########################################################################## */
/* ########################################################################## */
