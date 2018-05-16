#include <stdio.h>
#include <stdlib.h>

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


    if( ui_construct(&lContext) != EXIT_SUCCESS )
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


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
