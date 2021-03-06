#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL_ttf.h>

#include "core/input.h"
#include "core/macros.h"

#include "ui_menus.h"
#include "ui_private.h"
#include "ui_styles.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "ui", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "ui", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

int ui_construct(TContext *argContextPtr)
{
    int retVal  = EXIT_SUCCESS;


    /* Instanciate the struct */
    (*argContextPtr).ui = (TUiContext)malloc(sizeof(struct _SUiContextPrivate));

    /* Create a pointer for convenience */
    TUiContext  p_context   = (*argContextPtr).ui;

    p_context->screenBackgroundColor    = C_SDL_COLOR_BLACK;


    if( atexit( SDL_Quit ) != 0 )
    {
        TRACE_ERR( "Can't init SDL: Error while registering SDL_Quit" );

        retVal  = EXIT_FAILURE;
    }


    else if( (p_context->screen = SDL_SetVideoMode( C_SCREEN_WIDTH,
                                                    C_SCREEN_HEIGHT,
                                                    C_SCREEN_BPP,
                                                    SDL_HWSURFACE ) )
             == NULL )
    {
        TRACE_ERR( "Can't set video mode: %s",
                   SDL_GetError() );
        retVal  = EXIT_FAILURE;
    }
    else if( TTF_Init() == -1 )
    {
        TRACE_ERR( "Can't initialize SDL's TTF extension : %s",
                   TTF_GetError() );
        retVal  = EXIT_FAILURE;
    }


    /* -------------------------------------------------------------------------
     *  Init related variables
     */
    else if( ui_style_create( &(p_context->style_title),
                                  C_FONT_TRON,
                                  100,
                                  C_SDL_COLOR_YELLOW ) )
    {
        TRACE_ERR( "An error occured while creating TTF style 'title' !" );
        retVal  = EXIT_FAILURE;
    }
    else if( ui_style_create( &(p_context->style_game_scores),
                                  C_FONT_CONST1,
                                  20,
                                  C_SDL_COLOR_YELLOW ) )
    {
        TRACE_ERR("An error occured while creating TTF style 'game_scores' !");
        retVal  = EXIT_FAILURE;
    }
    else
    {
        input_init();
        TRACE_DBG( "UI init success." );
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int ui_destruct(TContext *argContext)
{
    int retVal  = EXIT_SUCCESS;


    if( argContext == NULL )
    {
        TRACE_ERR( "An invalid pointer has been given !" );
        retVal  = EXIT_FAILURE;
    }
    else
    {
        ui_style_delete( &(argContext->ui->style_game_scores) );
        ui_style_delete( &(argContext->ui->style_title) );

        TTF_Quit();
        SDL_Quit();
        FREE( argContext->ui )
    }


    return  retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int     ui_exec(TContext *argContext)
{
    int retVal  = EXIT_SUCCESS;


    /* Definition du nom de la fenetre */
    SDL_WM_SetCaption( "GoTron", NULL );

    retVal  = ui_menu_main( argContext );


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
