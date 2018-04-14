#include "cunit-core-gridData.h"

#include <stdlib.h>
#include <CUnit/Basic.h>

#include "core/grid.h"
#include "core/log/log.h"

/* ########################################################################## */
/* ########################################################################## */

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "cunit-core-gridData", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "cunit-core-gridData", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */


static  void    s_test_gridCreation(void)
{
    const size_t    C_GRID_COLSCOUNT    = 25;
    const size_t    C_GRID_ROWSCOUNT    = 25;

    TCoreGrid   lGridData   = grid_create( C_GRID_ROWSCOUNT, C_GRID_COLSCOUNT );


    /*
     *  Verification du contenu par defaut du tableau
     */
    for(size_t lRow = 0 ; lRow < C_GRID_ROWSCOUNT ; ++lRow  )
    {
        for( size_t lCol = 0 ; lCol < C_GRID_COLSCOUNT ; ++lCol )
        {
//            TRACE_DBG( "Testing Row %lu - Col %lu",
//                       lRow, lCol );
            /* Si la cellule fait partie du contour, alors ce doit être un mur*/
            if(     lRow == 0
                ||  lRow == C_GRID_ROWSCOUNT - 1
                ||  lCol == 0
                ||  lCol == C_GRID_COLSCOUNT - 1 )
            {
                CU_ASSERT_EQUAL_FATAL( grid_getCell( lGridData, lRow, lCol ),
                                       EGridCellWall );
            }
            /* Si la cellule ne fait pas partie du contour, alors elle doit etre
             * vide. */
            else
            {
                CU_ASSERT_EQUAL_FATAL( grid_getCell( lGridData, lRow, lCol ),
                                       EGridCellEmpty );
            }
        }
    }


    grid_destroy( lGridData );
}

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
static int  testSuite_init(void)
{
//   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
//      return -1;
//   }
//   else {
      return 0;
//   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
static int  testSuite_clean(void)
{
//   if (0 != fclose(temp_file)) {
//      return -1;
//   }
//   else {
//      temp_file = NULL;
      return 0;
//   }
}

int     testsInclude_cuinit_core_gridData()//CU_pSuite *argSuitePtr)
{
    int retVal  = EXIT_SUCCESS;


    CU_pSuite pSuite = NULL;

    /* add a suite to the registry */
    pSuite = CU_add_suite("suite-cuinit_core_gridData",
                          testSuite_init,
                          testSuite_clean );
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if( CU_add_test( pSuite, "Grid creation", s_test_gridCreation ) == NULL )
    {
        retVal  = EXIT_FAILURE;
    }


    return retVal;
}
