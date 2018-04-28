#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "ui/ui_game.h"
#include "ui/ui_private.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "tests-manu", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "tests-manu", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

int main(void)
{
    int retVal  = EXIT_SUCCESS;
    printf( "Hello %s !\n", __FILE__ );


    /*
     *  Init SDL
     */
    SDL_Surface*    p_screen   = NULL;

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        TRACE_ERR( "Can't init SDL:  %s",
                   SDL_GetError() );

        retVal  = EXIT_FAILURE;
    }

    else if( atexit( SDL_Quit ) != 0 )
    {
        TRACE_ERR( "Can't init SDL: Error while registering SDL_Quit" );

        retVal  = EXIT_FAILURE;
    }


    else if( ( p_screen = SDL_SetVideoMode( C_SCREEN_WIDTH,
                                            C_SCREEN_HEIGHT,
                                            C_SCREEN_BPP,
                                            SDL_HWSURFACE ) )
             == NULL )
    {
        TRACE_ERR( "Can't set video mode: %s",
                   SDL_GetError() );
        retVal  = EXIT_FAILURE;
    }



    /*
     *  Tests
     */
    TSCurrentGame lGame = ui_game_create( p_screen );


    /* Gestion affichage */
    ui_game_blit( lGame, p_screen );
    assert( SDL_Flip( p_screen ) != -1 && "SDL_Flip failure !" );



    getc(stdin);

    ui_game_destroy( &lGame );

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
