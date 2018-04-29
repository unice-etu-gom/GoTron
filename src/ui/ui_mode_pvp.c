#include "ui_mode_pvp.h"

#include <SDL.h>

#include "ui_game.h"
#include "ui_private.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "ui", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "ui", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

int ui_mode_pvp_exec(TContext argContext)
{
    TRACE_DBG( "Mode PvP activé." );


//    ui_surfaceFill( argContext.ui->screen,
//                    argContext.ui->screenBackgroundColor );

    argContext.ui->currentGame  = ui_game_create( argContext.ui->screen );


    SDL_Surface*    p_surf_tmpGame
            = SDL_CreateRGBSurface( 0,
                                    argContext.ui->screen->w,
                                    argContext.ui->screen->h,
                                    32,
                                    0, 0, 0, 0 );
    ui_game_blit( argContext.ui->currentGame, p_surf_tmpGame );


    ui_transition( argContext.ui->screen, p_surf_tmpGame, argContext.ui->screen );






    ui_surfaceClear( argContext.ui->screen );
    ui_game_blit( argContext.ui->currentGame, argContext.ui->screen );

    if( SDL_Flip( argContext.ui->screen ) == -1 )
    {
        TRACE_ERR( "SDL_Flip failure." );
    }
    getc(stdin);
    ui_game_destroy( &(argContext.ui->currentGame) );
}

/* ########################################################################## */
/* ########################################################################## */
