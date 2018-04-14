include_directories( ${SRC} )


set( DESTDIR_TESTS_AUTO ${DESTDIR_TESTS}/auto )


set( SRC_CUNIT
    cunit-main.c
    cunit-core-gridData.c
)



add_executable(         test-cunit  ${SRC_CUNIT} )
target_link_libraries(  test-cunit  core cunit ) # Define which libraries are needed by the target
set_target_properties ( test-cunit  PROPERTIES      LINK_FLAGS  -Wall )
set_target_properties(  test-cunit  PROPERTIES      RUNTIME_OUTPUT_DIRECTORY
                                                    ${DESTDIR_TESTS_AUTO} )
add_test(   test-cunit ${DESTDIR_TESTS_MANUELS}/test-cunit )
