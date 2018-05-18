#include <stdio.h>
#include <stdlib.h>

#include "core/data/highscores.h"

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

    highscoresList_load();

    return EXIT_SUCCESS;
}

/* ########################################################################## */
/* ########################################################################## */
