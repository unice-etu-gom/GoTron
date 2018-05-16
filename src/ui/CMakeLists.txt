set ( UI_SRC
    ui.c
    ui_game.c
    ui_game.h
    # ui_grid.c
    # ui_grid.h
    ui_menus.c
    ui_menus.h
    ui_mode_pvp.c
    ui_mode_pvp.h
    ui_mode_survival.c
    ui_mode_survival.h
    ui_private.c
    ui_private.h
    ui_styles.c
    ui_styles.h
    ui_text.c
    ui_text.h
)


add_library( ui STATIC ${UI_SRC} )
