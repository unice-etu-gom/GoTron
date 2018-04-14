set ( CORE_SRC
    grid.c

    log/log.h
)

#add_subdirectory( log )

add_library( core STATIC ${CORE_SRC} )
