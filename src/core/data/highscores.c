#include "highscores.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "core/macros.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "data", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "data", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

#define C_FILELINE_MAXLEN   (128)

const char*     C_DATA_SEPARATOR        = ";";
const char*     C_FILEPATH_HIGHSCORES   = "highscores.dat";
const size_t    C_HIGHSCORES_MAXCOUNT   = 10;

/* ########################################################################## */
/* ########################################################################## */

THighscoresListElt  highscoreElt_create(const char *argPseudo, int argScore)
{
    THighscoresListElt  retVal  = malloc( sizeof(struct _SHighscoresListElt) );

    retVal->next   = NULL;

    retVal->data.pseudo  = strdup( argPseudo );
    retVal->data.score   = argScore;


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    highscoreElt_destroy(THighscoresListElt *argElt)
{
    FREE( (*argElt)->data.pseudo );
    FREE( (*argElt) );
}

/* ########################################################################## */
/* ########################################################################## */

TBool   highscoresList_checkIfAccepted(THighscoresList argList, int argScore)
{
    size_t              lEltCount       = 0;
    THighscoresListElt  lEltIterator    = argList;
    TBool               retVal          = FALSE;


    /* If list is empty */
    if( lEltIterator == NULL )
    {
        retVal  = TRUE;
    }
    else
    {
        while(      lEltIterator != NULL
                &&  lEltCount < C_HIGHSCORES_MAXCOUNT )
        {
            if( argScore > lEltIterator->data.score )
            {
//                retVal  = TRUE;
                break;
            }

            lEltIterator    = lEltIterator->next;
            lEltCount++;
        }

        if( lEltCount < C_HIGHSCORES_MAXCOUNT )
        {
            retVal  = TRUE;
        }
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    highscoresList_delete(THighscoresList *argListPtr)
{
    THighscoresListElt  eltNext = NULL;

    while( *argListPtr != NULL )
    {
        eltNext = (*argListPtr)->next;

        highscoreElt_destroy( argListPtr );
        *argListPtr = eltNext;
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    highscoresList_insertEltOrdered( THighscoresList*       argListPtr,
                                         THighscoresListElt     argEltPtr )
{
    assert( argListPtr != NULL && "argListPtr must be valid !" );
    assert( argEltPtr != NULL && "argEltPtr must be valid !" );

    THighscoresList listHead    = *argListPtr;


    /* If the list is empty */
    if( listHead == NULL )
    {
        (*argListPtr)   = argEltPtr;
    }

    /* If the new element must be the first in the list */
    else if( argEltPtr->data.score > listHead->data.score )
    {
        argEltPtr->next = listHead;
        *argListPtr = argEltPtr;
    }
    else
    {
        THighscoresListElt  lEltIterator    = listHead;

        /* Loop until we find the right insertion position */
        while(      lEltIterator->next != NULL
               &&   lEltIterator->next->data.score > argEltPtr->data.score )
        {
            lEltIterator    = lEltIterator->next;
        }


        argEltPtr->next = lEltIterator->next;
        lEltIterator->next  = argEltPtr;
    }
}

/* ########################################################################## */
/* ########################################################################## */

THighscoresList highscoresList_load(void)
{
    char    lBuffer[C_FILELINE_MAXLEN]    = {0};
    FILE*   p_file  = fopen( C_FILEPATH_HIGHSCORES, "r" );

    THighscoresList retVal  = NULL;



    if( p_file == NULL )
    {
        TRACE_ERR( "No %s file !", C_FILEPATH_HIGHSCORES );
    }
    else
    {

        char*   lStrPtr = NULL;

        while( ! feof( p_file ) )
        {
            lStrPtr = fgets( lBuffer, C_FILELINE_MAXLEN, p_file );
            if( lStrPtr == NULL )
            {
                continue;
            }
            TRACE_DBG( "Reading line : %s", lBuffer );


            strtok( lBuffer, C_DATA_SEPARATOR );
//            TRACE_DBG( "First part : %s", lBuffer );

            lStrPtr = strtok( NULL, C_DATA_SEPARATOR );
//            TRACE_DBG( "Second part : %s", lStrPtr );


            THighscoresListElt  lElt
                    = highscoreElt_create( lBuffer, strtol(lStrPtr, NULL, 10) );

//            TRACE_DBG( "+-- Highscore :" );
//            TRACE_DBG( "    +-- %s \t: %d",
//                       lElt->data.pseudo,
//                       lElt->data.score );

            highscoresList_insertEltOrdered( &retVal, lElt );


        }

        fclose( p_file );
    }


    highscoresList_print( retVal );
    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    highscoresList_print(THighscoresList argList)
{
    THighscoresListElt  elt = argList;

    TRACE_DBG( "+-- Highscores list :" );

    while( elt != NULL )
    {
        TRACE_DBG( "    +-- Highscore :" );
        TRACE_DBG( "        +-- Pseudo \t: %s",
                   elt->data.pseudo );
        TRACE_DBG( "        +-- Score \t: %d",
                   elt->data.score );

        elt = elt->next;
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    highscoresList_save(THighscoresList argList)
{


    char    lBuffer[C_FILELINE_MAXLEN]    = {0};
    FILE*   p_file  = fopen( C_FILEPATH_HIGHSCORES, "w" );

    THighscoresList retVal  = NULL;



    if( p_file == NULL )
    {
        TRACE_ERR( "Error while openign file '%s' ! %s",
                   C_FILEPATH_HIGHSCORES,
                   strerror( errno ) );
    }
    else
    {

        THighscoresListElt  lEltIterator    = argList;


        while( lEltIterator != NULL )
        {
            fprintf( p_file, "%s;%d\n",
                     lEltIterator->data.pseudo,
                     lEltIterator->data.score );


            lEltIterator    = lEltIterator->next;
        }

        fclose( p_file );
    }
}
