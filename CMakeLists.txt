
# ------------------------------------------------------------------------------
#   CMake requirements
# ------------------------------------------------------------------------------

# cmake version
cmake_minimum_required ( VERSION 2.8.10 FATAL_ERROR )



# ------------------------------------------------------------------------------
#   Project global configuration
# ------------------------------------------------------------------------------
# define project name and langage
project( GoTron C )

# define executable names
set ( EXE ${PROJECT_NAME} )

# set( DESTDIR_APP ${CMAKE_SOURCE_DIR}/out/app )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/app )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib )



# ------------------------------------------------------------------------------
# Include external libraries
# ------------------------------------------------------------------------------
# # ncurses
# find_package( Curses REQUIRED )
# include_directories( ${CURSES_INCLUDE_DIR} )
# set( CURSES_LIBS -lmenu -lncurses )
# 
# # CDK
# set( CDK_LIBS -lcdk )

# SDL
FIND_PACKAGE(SDL        REQUIRED)
FIND_PACKAGE(SDL_ttf    REQUIRED)
FIND_PACKAGE(SDL_mixer  REQUIRED)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})



# ------------------------------------------------------------------------------
#   Include source subdirectories
# ------------------------------------------------------------------------------
set ( SRC ${CMAKE_SOURCE_DIR}/src )
add_subdirectory( ${SRC} )



# ------------------------------------------------------------------------------
#   Configuration liee aux tests
# ------------------------------------------------------------------------------
ENABLE_TESTING()
set( TESTS ${CMAKE_SOURCE_DIR}/tests )
add_subdirectory( ${TESTS} )
