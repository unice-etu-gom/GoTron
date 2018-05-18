set ( CORE_SRC
    grid.c
    input.c
    input.h

    macros.h
    TBool.h
    TPosition2D.h

    data/highscores.c
    data/highscores.h
    log/log.h
)

#add_subdirectory( log )

add_library( core STATIC ${CORE_SRC} )
