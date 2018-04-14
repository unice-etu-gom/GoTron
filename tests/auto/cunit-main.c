#include <CUnit/Basic.h>

#include <stdlib.h>

#include "core/log/log.h"

#include "cunit-core-gridData.h"

/* ########################################################################## */
/* ########################################################################## */

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "cunit-main", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "cunit-main", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

int init_testRegistry(void)
{
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }
    else
    {
        return 0;
    }
}

/* ########################################################################## */
/* ########################################################################## */

int    init_testSuite(void)
{
//    CU_pSuite pSuite = NULL;

//    /* add a suite to the registry */
//    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
//    if (NULL == pSuite)
//    {
//        CU_cleanup_registry();
//        return CU_get_error();
//    }


//    /* add the tests to the suite */
//    if( testsInclude_cuinit_core_gridData( &pSuite ) != EXIT_SUCCESS )
//    {
//        CU_cleanup_registry();
//        return CU_get_error();
//    }

    testsInclude_cuinit_core_gridData();
//#if 0
//    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
//    if ((NULL == CU_add_test(pSuite, "test of fprintf()", testFPRINTF)) ||
//        (NULL == CU_add_test(pSuite, "test of fread()", testFREAD)))
//    {
//        CU_cleanup_registry();
//        return CU_get_error();
//    }
//#endif
}

/* ########################################################################## */
/* ########################################################################## */

int main()
{

    if( init_testRegistry() )
    {
       TRACE_ERR( "Test registry initialization error : %s",
                  CU_get_error_msg() );
        return CU_get_error();
    }

    else if( init_testSuite() )
    {
        TRACE_ERR( "Test registry initialization error : %s",
                   CU_get_error_msg() );
         return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

/* ########################################################################## */
/* ########################################################################## */
