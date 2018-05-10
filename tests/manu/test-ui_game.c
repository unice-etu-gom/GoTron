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

static void test_transition(SDL_Surface* argScreenSurfacePtr)
{
    /*
     *  Draw a background on the screen as the "old" surface
     */
    SDL_Surface* p_surf_old
            = SDL_CreateRGBSurface( 0,
                                    argScreenSurfacePtr->w,
                                    argScreenSurfacePtr->h,
                                    32,
                                    0, 0, 0, 0 );

    /* Fill the background with a specific color */
    ui_surfaceFill( p_surf_old, C_SDL_COLOR_YELLOW );

    /* Display the background on the screen */
    SDL_BlitSurface( p_surf_old, NULL, argScreenSurfacePtr, NULL );
    SDL_Flip( argScreenSurfacePtr );


    SStyle  lStyle;
    ui_style_create( &lStyle, C_FONT_TRON, 10, C_SDL_COLOR_YELLOW );


    /*
     *  Create a game grid as the new surface.
     * We do not use a uniform surface as it is interesting to see the behaviour
     * of a "complex" surface.
     */
    TSCurrentGame lGame = ui_game_create( argScreenSurfacePtr,
                                          lStyle );

    /* The game grid is blitted to a new surface */
    SDL_Surface* p_surf_new
            =  SDL_CreateRGBSurface( 0,
                                     argScreenSurfacePtr->w,
                                     argScreenSurfacePtr->h,
                                     32,
                                     0, 0, 0, 0 );
    ui_game_blit( lGame, p_surf_new, UI_GAME_FLAG_LAYERS_ALL );



    /*
     *  Proceed the transition from the old background surface to the new grid
     * surface.
     */
    ui_transition( p_surf_old, p_surf_new, argScreenSurfacePtr );


//    assert( SDL_Flip( argScreenSurfacePtr ) != -1 && "SDL_Flip failure !" );



    /* Wait a user action to continue */
    getc(stdin);


    /* Free resources */
    SDL_FreeSurface( p_surf_new );
    SDL_FreeSurface( p_surf_old );
    ui_game_destroy( &lGame );
    ui_style_delete( &lStyle );
}

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
     *  Execute tests
     */
    test_transition( p_screen );


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
