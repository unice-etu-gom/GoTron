#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "core/audio.h"
#include "core/TContext.h"
#include "ui/ui.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "main", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "main", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

int     main(void)
{
    int retVal  = EXIT_SUCCESS;


    printf( "Hello, world !\n" );

    TContext    lContext    = {0};


    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        TRACE_ERR( "Can't init SDL:  %s",
                   SDL_GetError() );

        retVal  = EXIT_FAILURE;
    }
    else if( audio_construct( &(lContext.audio) ) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while initializing Audio interface !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ui_construct(&lContext) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while constructing UI !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ui_exec( &lContext ) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while executing UI !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ui_destruct(&lContext) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while destructing UI !" );
        retVal  = EXIT_FAILURE;
    }
    else if( audio_destruct(&lContext.audio) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while destructing UI !" );
        retVal  = EXIT_FAILURE;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
