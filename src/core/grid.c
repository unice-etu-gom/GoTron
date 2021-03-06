#include "grid.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef  TEST
#   include <stdio.h>
#endif

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

#define C_CHAR_CELLTYPE_EMPTY   ('e')
#define C_CHAR_CELLTYPE_PLAYER1 ('1')
#define C_CHAR_CELLTYPE_PLAYER2 ('2')
#define C_CHAR_CELLTYPE_UNKNOWN ('u')
#define C_CHAR_CELLTYPE_WALL    ('W')

/* ########################################################################## */
/* ########################################################################## */

struct  _SCoreGrid
{
    size_t  rowsCount;
    size_t  columsCount;

    TEGridCellType  *data;
};

/* ########################################################################## */
/* ########################################################################## */

TEGridCellType grid_cellType_fromChar(const char argChar)
{
    TEGridCellType  retVal  = EGridCellUnknown;


    switch( argChar )
    {
        case    C_CHAR_CELLTYPE_EMPTY:
            retVal  = EGridCellEmpty;
            break;


        case    C_CHAR_CELLTYPE_WALL:
            retVal  = EGridCellWall;
            break;


        default:
            break;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

char grid_cellType_toChar(const TEGridCellType argType)
{
    char    retVal  = '?';

    switch( argType )
    {
        case    EGridCellEmpty:
            retVal  = C_CHAR_CELLTYPE_EMPTY;
            break;


        case    EGridCellPlayer1:
            retVal  = C_CHAR_CELLTYPE_PLAYER1;
            break;


        case    EGridCellPlayer2:
            retVal  = C_CHAR_CELLTYPE_PLAYER2;
            break;


        case    EGridCellUnknown:
            retVal  = C_CHAR_CELLTYPE_UNKNOWN;
            break;


        case    EGridCellWall:
            retVal  = C_CHAR_CELLTYPE_WALL;
            break;


        default:
            TRACE_ERR( "Unknown cell type with value %d !",
                       argType );
            break;
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

size_t  grid_columnsCount(TCoreGrid argGrid)
{
    return  argGrid->columsCount;
}

/* ########################################################################## */
/* ########################################################################## */

TCoreGrid   grid_create(size_t argCols, size_t argRows)
{
    struct _SCoreGrid* retVal
            = (struct _SCoreGrid*)malloc( sizeof( struct _SCoreGrid ) );


    /* Initialize struct's "simple" members */
    retVal->columsCount = argCols;
    retVal->rowsCount   = argRows;
    retVal->data        = NULL;


    /* Allocate memory for the grid data depending on the grid size */
    size_t lCellsCount  = retVal->columsCount * retVal->rowsCount;

    retVal->data    = (TEGridCellType*)malloc(      sizeof( TEGridCellType )
                                                *   lCellsCount );

    /* Initialize grid content to the default value */
    for( size_t i = 0 ; i < lCellsCount ; ++i )
    {
        retVal->data[ i ]   = EGridCellEmpty;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    grid_destroy( TCoreGrid argGrid )
{
    FREE( (argGrid->data) );
    FREE( argGrid );
}

/* ########################################################################## */
/* ########################################################################## */

TEGridCellType  grid_getCell( TCoreGrid argGrid,
                              size_t    argRow,
                              size_t    argCol )
{
    assert( argCol  < argGrid->columsCount);
    assert( argRow  < argGrid->rowsCount  );


    return argGrid->data[argRow * argGrid->columsCount + argCol];
}

/* ########################################################################## */
/* ########################################################################## */
#ifdef  TEST
void    grid_print(TCoreGrid argGrid)
{
    for(size_t row = 0 ; row < argGrid->rowsCount ; row++ )
    {
        for( size_t col = 0 ; col < argGrid->columsCount ; col++ )
        {
            putc( grid_cellType_toChar( grid_getCell( argGrid, row, col ) ),
                  stdout );

            putc( ' ', stdout );
        }

        putc( '\n', stdout );
    }
}
#endif
/* ########################################################################## */
/* ########################################################################## */

size_t  grid_rowsCount(TCoreGrid argGrid)
{
    return  argGrid->rowsCount;
}

/* ########################################################################## */
/* ########################################################################## */

void    grid_setCell( TCoreGrid         argGrid,
                      size_t            argRow,
                      size_t            argCol,
                      TEGridCellType    argCellType )
{
    assert( argCol  < argGrid->columsCount);
    assert( argRow  < argGrid->rowsCount  );


    argGrid->data[argRow * argGrid->columsCount + argCol]   = argCellType;
}

/* ########################################################################## */
/* ########################################################################## */
