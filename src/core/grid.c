#include "grid.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef  TEST
#   include <stdio.h>
#endif

/* ########################################################################## */
/* ########################################################################## */

#define C_CHAR_CELLTYPE_EMPTY   (' ')
#define C_CHAR_CELLTYPE_PLAYER1 ('1')
#define C_CHAR_CELLTYPE_PLAYER2 ('2')
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


        case    EGridCellWall:
            retVal  = C_CHAR_CELLTYPE_WALL;
            break;


        default:
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
    TCoreGrid   retVal  = (TCoreGrid)malloc( sizeof( struct _SCoreGrid ) );


    retVal->columsCount = argCols;
    retVal->rowsCount   = argRows;

    int lCellsCount = retVal->columsCount * retVal->rowsCount;

    retVal->data    = (TEGridCellType*)malloc(      sizeof( TEGridCellType )
                                                *   lCellsCount );

    memset(retVal->data, EGridCellEmpty, lCellsCount);



    /*
     *  Create the borders
     */
    for(    size_t lRowNbr = 0
        ;   lRowNbr < argRows
        ;   ++lRowNbr )
    {
        grid_setCell( retVal, lRowNbr, 0,           EGridCellWall );
        grid_setCell( retVal, lRowNbr, argCols - 1, EGridCellWall );
    }

    for(    size_t lColNbr = 0
        ;   lColNbr < argCols
        ;   ++lColNbr )
    {
        grid_setCell( retVal, 0,            lColNbr,    EGridCellWall );
        grid_setCell( retVal, argRows - 1,  lColNbr,    EGridCellWall );
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    grid_destroy(TCoreGrid argGrid)
{
    free( argGrid->data );
    free( (struct _SCoreGrid*)argGrid );
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
