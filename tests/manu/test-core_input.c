#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "core/input.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "test", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "test", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

int main(void)
{
    printf( "Hello test !\n" );


    /* Initialise SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
        fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
        exit( -1 );
    }

    /* Set a video mode */
    if( !SDL_SetVideoMode( 320, 200, 0, 0 ) ){
        fprintf( stderr, "Could not set video mode: %s\n", SDL_GetError() );
        SDL_Quit();
        exit( -1 );
    }

    input_init();


//    TKeyboardInput lKI  = keyboardInput_create();

//    keyboardInput_start( lKI );

#if 1
    for( int i = 0 ; i < 5 ; ++i )
#else
        while (1)
#endif
    {
        TRACE_DBG( "**** Depilement ****" );

        SDLKey lKey = SDLK_UNKNOWN;
        while( (lKey=input_keyboardEvent_poll()) != SDLK_UNKNOWN )
        {
            if( lKey != 0 )
            {
                TRACE_DBG( "    +-- Dépilé appui touche %c",
                           (char)lKey );
            }
            else
            {
                TRACE_DBG( "    +-- Lecture non valide" );
            }
        } while( lKey != 0 );

        TRACE_DBG( "---- FIN Depilement ----" );


        /* Delai volontairement long pour permettre d'accumuler des events */
        SDL_Delay( 2000 );
    }

//    keyboardInput_destroy( &lKI );


    return EXIT_SUCCESS;
}

