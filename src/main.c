#include <stdio.h>
#include <stdlib.h>

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

    TUiContext  lUiContext  = NULL;


    if( ui_construct(&lUiContext) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while constructing UI !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ui_exec( &lUiContext ) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while executing UI !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ui_destruct(&lUiContext) != EXIT_SUCCESS )
    {
        TRACE_ERR( "Error while destructing UI !" );
        retVal  = EXIT_FAILURE;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
