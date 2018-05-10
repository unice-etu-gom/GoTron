#include "input.h"

#include <assert.h>

#include <SDL_events.h>
#include <SDL_thread.h>
#include <SDL_timer.h>

#include "core/TBool.h"
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

void    input_init(void)
{
    /* Enable Unicode translation */
    SDL_EnableUNICODE( 1 );
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief
 *
 *  @retval SDLK_UNKNOWN    If no key can be read.
 */
SDLKey  input_keyboardEvent_poll(void)
{
    SDL_Event   lEvent;
    SDLKey      retVal  = SDLK_UNKNOWN;

    TBool   lEventTypeIsOK  = FALSE;


//    TRACE_DBG( "Looking for an event..." );
    /* Poll for events */
    while(      SDL_PollEvent( &lEvent )    != 0
            &&  lEventTypeIsOK              != TRUE )
    {
        switch( lEvent.type )
        {
            /* case SDL_KEYUP: */
            case SDL_KEYDOWN:
                lEventTypeIsOK  = TRUE;
                input_printKeyInfo( &lEvent.key );
                retVal  = lEvent.key.keysym.sym;
                break;


#if 0
            /* Not managed here. */
            /* SDL_QUIT event (window close) */
            case SDL_QUIT:
                quit = 1;
                break;
#endif


            default:
                break;
        }
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    input_printKeyInfo( SDL_KeyboardEvent *key )
{
    /* Is it a release or a press? */
    if( key->type == SDL_KEYUP )
        printf( "Release:- " );
    else
        printf( "Press:- " );


    /* Print the hardware scancode first */
    printf( "Scancode: 0x%02X", key->keysym.scancode );
    /* Print the name of the key */
    printf( ", Name: %s", SDL_GetKeyName( key->keysym.sym ) );
    /* We want to print the unicode info, but we need to make */
    /* sure its a press event first (remember, release events */
    /* don't have unicode info                                */
    if( key->type == SDL_KEYDOWN )
    {
        /* If the Unicode value is less than 0x80 then the    */
        /* unicode value can be used to get a printable       */
        /* representation of the key, using (char)unicode.    */
        printf(", Unicode: " );
        if( key->keysym.unicode < 0x80 && key->keysym.unicode > 0 )
        {
            printf( "%c (0x%04X)", (char)key->keysym.unicode,
                    key->keysym.unicode );
        }
        else
        {
            printf( "? (0x%04X)", key->keysym.unicode );
        }
    }
    printf( "\n" );
    /* Print modifier info */
    input_printModifiers( key->keysym.mod );
}

/* ########################################################################## */
/* ########################################################################## */

void    input_printModifiers( SDLMod mod )
{
    printf( "Modifers: " );

    /* If there are none then say so and return */
    if( mod == KMOD_NONE )
    {
        printf( "None\n" );
        return;
    }

    /* Check for the presence of each SDLMod value */
    /* This looks messy, but there really isn't    */
    /* a clearer way.                              */
    if( mod & KMOD_NUM ) printf( "NUMLOCK " );
    if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
    if( mod & KMOD_LCTRL ) printf( "LCTRL " );
    if( mod & KMOD_RCTRL ) printf( "RCTRL " );
    if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
    if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
    if( mod & KMOD_RALT ) printf( "RALT " );
    if( mod & KMOD_LALT ) printf( "LALT " );
    if( mod & KMOD_CTRL ) printf( "CTRL " );
    if( mod & KMOD_SHIFT ) printf( "SHIFT " );
    if( mod & KMOD_ALT ) printf( "ALT " );
    printf( "\n" );
}

/* ########################################################################## */
/* ########################################################################## */
#if 0
typedef struct SEventThreadData
{
    SDL_sem*    p_sem_dataProtect;

    SDL_sem*    p_sem_quit;

    char    lastKey_player1;
    char    lastKey_player2;

}   TSEventThreadData;


struct SKeyboardInput
{
    TSEventThreadData   threadDataStruct;
    SDL_Thread*         p_sdl_thread;
};

static void s_dataLockTake( TSEventThreadData* argDataPtr );
static void s_dataLockRelease( TSEventThreadData* argDataPtr );
static int  s_eventThread(void* argData);
#endif

/* ########################################################################## */
/* ########################################################################## */
#if 0
void    s_dataLockRelease( TSEventThreadData* argDataPtr )
{
    assert( argDataPtr != NULL && "argDataPtr must NOT be null !" );

    SDL_SemPost( (*argDataPtr).p_sem_dataProtect );
}

/* ########################################################################## */
/* ########################################################################## */

void    s_dataLockTake( TSEventThreadData* argDataPtr )
{
    assert( argDataPtr != NULL && "argDataPtr must NOT be null !" );

    SDL_SemWait( (*argDataPtr).p_sem_dataProtect );
}

/* ########################################################################## */
/* ########################################################################## */

int     s_eventThread(void* argData)
{
    TSEventThreadData*  p_data  = (TSEventThreadData*)argData;

    SDL_Event           lEvent;


    //Tant que l'arrêt n'est pas demadé
    while( SDL_SemTryWait( p_data->p_sem_quit ) != 0 )
    {
#if 0
        //On anime le log
        TRACE_DBG( "Thread is running -" );
        SDL_Delay( 250 );

        TRACE_DBG( "Thread is running \\" );
        SDL_Delay( 250 );

        TRACE_DBG( "Thread is running |" );
        SDL_Delay( 250 );

        TRACE_DBG( "Thread is running /" );
        SDL_Delay( 250 );
#endif

        /* Poll for events */
        while(      SDL_PollEvent( &lEvent )
                &&  SDL_SemTryWait( p_data->p_sem_quit ) != 0 )
        {
            switch( lEvent.type )
            {
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
                case SDL_KEYDOWN:
//                case SDL_KEYUP:
                    s_PrintKeyInfo( &lEvent.key );
                    switch( lEvent.key.keysym.unicode )
                    {
                        case    'Z':
                        case    'z':
                        case    'Q':
                        case    'q':
                        case    'S':
                        case    's':
                        case    'D':
                        case    'd':
                            TRACE_DBG ( "Mouvement joueur 1" );
                            s_dataLockTake( p_data );
                            p_data->lastKey_player1
                                    = (char)lEvent.key.keysym.unicode;
                            s_dataLockRelease( p_data );
                            break;


                        case    SDLK_LEFT:
                        case    SDLK_RIGHT:
                        case    SDLK_UP:
                        case    SDLK_DOWN:
                            TRACE_DBG ( "Mouvement joueur 2" );
                            s_dataLockTake( p_data );
                            p_data->lastKey_player2
                                    = (char)lEvent.key.keysym.unicode;
                            s_dataLockRelease( p_data );
                            break;


                        default:
                            TRACE_DBG ( "Touche inconnue ! %c",
                                        lEvent.key.keysym.unicode );
                            break;
                    }

                    break;


#if 0
                /* Not managed here. */
                /* SDL_QUIT event (window close) */
                case SDL_QUIT:
                    quit = 1;
                    break;
#endif


                default:
                    break;
            }

        }
    }


    return 0;
}
#endif
/* ########################################################################## */
/* ########################################################################## */
#if 0
TKeyboardInput  keyboardInput_create(void)
{
    TKeyboardInput  retVal  = malloc( sizeof(struct SKeyboardInput ) );
    assert( retVal != NULL && "TKeyboardInput struct memory allocation error" );


    retVal->p_sdl_thread    = NULL;
    retVal->threadDataStruct.lastKey_player1    = '\0';
    retVal->threadDataStruct.lastKey_player2    = '\0';
    retVal->threadDataStruct.p_sem_dataProtect  = SDL_CreateSemaphore( 1 );
    retVal->threadDataStruct.p_sem_quit         = SDL_CreateSemaphore( 0 );
}

/* ########################################################################## */
/* ########################################################################## */

void    keyboardInput_destroy( TKeyboardInput* argEltToDestroy)
{
    assert( argEltToDestroy != 0 && "argEltToDestroy must not be NULL !" );


    if( (*argEltToDestroy) == NULL )
    {
        TRACE_ERR( "argEltToDestroy hasn't previously been created !" );
        return;
    }


    /* Arrêt du thread */
    keyboardInput_stop( (*argEltToDestroy) );

    /* Liberation des ressources */
    SDL_DestroySemaphore( (*argEltToDestroy)->threadDataStruct.
                          p_sem_dataProtect );
    SDL_DestroySemaphore( (*argEltToDestroy)->threadDataStruct.p_sem_quit );

    /* Destruction de l'objet */
    FREE( (*argEltToDestroy) );
}

/* ########################################################################## */
/* ########################################################################## */

void    keyboardInput_start(TKeyboardInput argElt)
{
    if( argElt->p_sdl_thread != NULL )
    {
        TRACE_DBG( "Tried to start an already created thread." );
    }
    else
    {
        argElt->p_sdl_thread    = SDL_CreateThread( s_eventThread,
                                                    &argElt->threadDataStruct );
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    keyboardInput_stop(TKeyboardInput argElt)
{
    /* Demande fin du thread */
    SDL_SemPost( argElt->threadDataStruct.p_sem_quit );

    /* Attente fin du thread */
    int lStatus = 0;
    SDL_WaitThread( argElt->p_sdl_thread, &lStatus );
//    SDL_KillThread( argElt->p_sdl_thread );
    argElt->p_sdl_thread    = NULL;

//    TRACE_DBG( "argElt->p_sdl_thread vaut 0x%0X",
//               (unsigned int)argElt->p_sdl_thread );
}
#endif
/* ########################################################################## */
/* ########################################################################## */
