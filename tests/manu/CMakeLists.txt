include_directories( ${SRC} )


set( DESTDIR_TESTS_MANUELS ${DESTDIR_TESTS}/manu )



# define the executable in terms of the source files
add_executable(         test-gridData test-gridData.c )
target_link_libraries(  test-gridData core ) # Define which libraries are needed by the target
set_target_properties(  test-gridData PROPERTIES    LINKER_LANGUAGE C )
set_target_properties(  test-gridData PROPERTIES    RUNTIME_OUTPUT_DIRECTORY
                                                    ${DESTDIR_TESTS_MANUELS} )



# define the executable in terms of the source files
add_executable(         test-core_input test-core_input.c )
target_link_libraries(  test-core_input
                        core
                        ${SDL_LIBRARY}
                        ${SDL_TTF_LIBRARY} ) # Define which libraries are needed by the target
set_target_properties(  test-core_input PROPERTIES  LINKER_LANGUAGE C )
set_target_properties(  test-core_input PROPERTIES  RUNTIME_OUTPUT_DIRECTORY
                                                    ${DESTDIR_TESTS_MANUELS} )



# define the executable in terms of the source files
add_executable(         test-core_data_highscores test-core_data_highscores.c )
target_link_libraries(  test-core_data_highscores
                        core
                        ${SDL_LIBRARY}
                        ${SDL_TTF_LIBRARY} ) # Define which libraries are needed by the target
set_target_properties(  test-core_data_highscores   PROPERTIES  LINKER_LANGUAGE C )
set_target_properties(  test-core_data_highscores   PROPERTIES  RUNTIME_OUTPUT_DIRECTORY
                                                                ${DESTDIR_TESTS_MANUELS} )



add_executable(         test-ui_game test-ui_game.c )
# Define which libraries are needed by the target
target_link_libraries(  test-ui_game
                        ui
                        core
                        ${SDL_LIBRARY}
                        ${SDL_TTF_LIBRARY} )
set_target_properties(  test-ui_game PROPERTIES LINKER_LANGUAGE C )
set_target_properties(  test-ui_game PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                ${DESTDIR_TESTS_MANUELS} )
