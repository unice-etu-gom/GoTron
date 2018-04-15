set ( CORE_SRC
    grid.c

    macros.h
    TBool.h

    log/log.h
)

#add_subdirectory( log )

add_library( core STATIC ${CORE_SRC} )
