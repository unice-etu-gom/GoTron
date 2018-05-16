#include "ui_menus.h"

#include "core/input.h"
#include "core/macros.h"
#include "core/TBool.h"
#include "core/TContext.h"

#include "ui_mode_pvp.h"
#include "ui_mode_survival.h"
#include "ui_private.h"
#include "ui_styles.h"
#include "ui_text.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "ui", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "ui", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

int     ui_menu_main(TContext *argContextPtr)
{
    int retVal  = EXIT_SUCCESS;


    TUiContext  p_contextUi = argContextPtr->ui;



    /* -------------------------------------------------------------------------
     *  Creation des surfaces
     */
    SStyle  lStyleItemDefault;
    ui_style_create( &lStyleItemDefault, C_FONT_TRON, 30, C_SDL_COLOR_BLUE );

    SStyle  lStyleItemHovered;
    ui_style_create( &lStyleItemHovered, C_FONT_TRON, 30, C_SDL_COLOR_PINK );


    TUiText txtTitle    = ui_text_create( "Go_Tron",
                                          p_contextUi->style_title );

    TUiText txtSurvival = ui_text_create( "Survival",
                                          lStyleItemDefault );

    TUiText txtPvP      = ui_text_create( "Player Vs Player",
                                          lStyleItemDefault );

    TUiText txtPvAI     = ui_text_create( "Player Vs AI",
                                          lStyleItemDefault );

    TUiText txtExit     = ui_text_create( "Exit",
                                          lStyleItemDefault );


    if( txtTitle == NULL )
    {
        retVal  = EXIT_FAILURE;
        TRACE_ERR( "Text rendering error : %s",
                   TTF_GetError() );
    }

    ui_text_setAlign( txtTitle, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtTitle,
                    C_SCREEN_WIDTH / 2,
                    ui_text_getRect(txtTitle).h );


    int lPosY   = C_SCREEN_HEIGHT / 2;
    ui_text_setAlign( txtSurvival, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtSurvival,
                    C_SCREEN_WIDTH / 2,
                    lPosY );
    lPosY   += ui_text_getRect( txtSurvival ).h * 2;

    ui_text_setAlign( txtPvP, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtPvP,
                    C_SCREEN_WIDTH / 2,
                    lPosY );
    lPosY   += ui_text_getRect( txtPvP ).h * 2;

    ui_text_setAlign( txtPvAI, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtPvAI,
                    C_SCREEN_WIDTH / 2,
                    lPosY );
    lPosY   += ui_text_getRect( txtPvAI ).h * 2;

    ui_text_setAlign( txtExit, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtExit,
                    C_SCREEN_WIDTH / 2,
                    lPosY );



    /* -------------------------------------------------------------------------
     *  Application des surfaces et affichage
     */
    /*
     *  Partie 1 : Fade-in titre
     */

    for( uint lAlpha = 0U ; lAlpha <= 255U ; ++lAlpha )
    {
        ui_text_setAlpha( txtTitle, lAlpha );

        ui_surfaceFill( p_contextUi->screen,
                         argContextPtr->ui->screenBackgroundColor );
        ui_text_blit( txtTitle, p_contextUi->screen );


        if( SDL_Flip( p_contextUi->screen ) == -1 )
        {
            return EXIT_FAILURE;
        }

//        SDL_Delay( 5 );
    }


    /*
     *  Partie 2 : Fade-in items menu
     */
    for( uint lAlpha = 0U ; lAlpha <= 255U ; ++lAlpha )
    {
        ui_text_setAlpha( txtSurvival,  lAlpha );
        ui_text_setAlpha( txtExit,      lAlpha );
        ui_text_setAlpha( txtPvAI,      lAlpha );
        ui_text_setAlpha( txtPvP,       lAlpha );


        ui_surfaceFill( p_contextUi->screen,
                         argContextPtr->ui->screenBackgroundColor );

        ui_text_blit( txtSurvival,  p_contextUi->screen );
        ui_text_blit( txtExit,      p_contextUi->screen );
        ui_text_blit( txtPvAI,      p_contextUi->screen );
        ui_text_blit( txtPvP,       p_contextUi->screen );
        ui_text_blit( txtTitle,     p_contextUi->screen );


        if( SDL_Flip( p_contextUi->screen ) == -1 )
        {
            return EXIT_FAILURE;
        }

//        SDL_Delay( 5 );
    }



    /* -------------------------------------------------------------------------
     *  Partie 3 : Execution de la boucle de gestion des evenements
     */
    SDL_Event   lSdlEvent;
    TBool       lFlagQuit   = FALSE;

    enum EMenuItems
    {
        EMenuItemSurvival = 0,
        EMenuItemPvP,
        EMenuItemPvAI,
        EMenuItemExit,

        EMenuItemsCount
    };
    int     lCurrentChoice  = EMenuItemSurvival;
    TBool   lFlagChoiceOK   = FALSE;


    input_flushPendingEvents();

    do
    {
        /* ---------------------------------------------------------------------
         *  Manage display
         */
        ui_text_setStyle( txtSurvival,  lStyleItemDefault );
        ui_text_setStyle( txtExit,      lStyleItemDefault );
        ui_text_setStyle( txtPvAI,      lStyleItemDefault );
        ui_text_setStyle( txtPvP,       lStyleItemDefault );

        switch( lCurrentChoice )
        {
            case EMenuItemSurvival:
                ui_text_setStyle( txtSurvival, lStyleItemHovered );
                break;


            case EMenuItemExit:
                ui_text_setStyle( txtExit, lStyleItemHovered );
                break;


            case EMenuItemPvAI:
                ui_text_setStyle( txtPvAI, lStyleItemHovered );
                break;


            case EMenuItemPvP:
                ui_text_setStyle( txtPvP, lStyleItemHovered );
                break;


            default:
                TRACE_ERR( "Unknown item index (%d) !",
                           lCurrentChoice );
                break;
        }


        ui_surfaceFill( p_contextUi->screen,
                         argContextPtr->ui->screenBackgroundColor );

        ui_text_blit( txtSurvival,  p_contextUi->screen );
        ui_text_blit( txtExit,      p_contextUi->screen );
        ui_text_blit( txtPvAI,      p_contextUi->screen );
        ui_text_blit( txtPvP,       p_contextUi->screen );
        ui_text_blit( txtTitle,     p_contextUi->screen );


        if( SDL_Flip( p_contextUi->screen ) == -1 )
        {
            return 1;
        }



        /* ---------------------------------------------------------------------
         *  Intercept events and interpret them
         */
        SDL_WaitEvent( &lSdlEvent );
        switch( lSdlEvent.type )
        {
            case    SDL_KEYDOWN:
                switch( lSdlEvent.key.keysym.sym )
                {
                    case    SDLK_DOWN:
                        lCurrentChoice++;
                        break;


                    case    SDLK_UP:
                        lCurrentChoice--;
                        break;


                    case    SDLK_RETURN:
                        lFlagChoiceOK   = TRUE;
                        break;


                    default:
                        break;
                }
                break;


            case    SDL_QUIT:
                lFlagQuit   = TRUE;
                break;


            default:
                break;
        }


        /* Keep the index in the acceptable range */
        lCurrentChoice  %= EMenuItemsCount;
        while( lCurrentChoice < 0 )
        {
            lCurrentChoice  += EMenuItemsCount;
        }



        /* ---------------------------------------------------------------------
         *  Manage actions execution
         */
        if( lFlagChoiceOK )
        {
            lFlagChoiceOK   = FALSE;
            switch( lCurrentChoice )
            {
                case    EMenuItemSurvival:
                {
                    /* Backup affichage menu */
                    SDL_Surface* p_surfMenuOld
                            = SDL_CreateRGBSurface( 0,
                                                    p_contextUi->screen->w,
                                                    p_contextUi->screen->h,
                                                    32,
                                                    0, 0, 0, 0 );
                    SDL_BlitSurface( p_contextUi->screen,
                                     NULL,
                                     p_surfMenuOld,
                                     NULL );

                    /* Execution mode PvP */
                    ui_mode_survival_exec( *argContextPtr );

                    /* Restauration affichage menu */
                    ui_transition( p_contextUi->screen,
                                   p_surfMenuOld,
                                   p_contextUi->screen );
                    SDL_FreeSurface( p_surfMenuOld );
                }
                    break;


                case EMenuItemExit:
                    lFlagQuit   = TRUE;
                    break;

#if 0
                case EMenuItemPvAI:
                    break;
#endif


                case    EMenuItemPvP:
                {
                    /* Backup affichage menu */
                    SDL_Surface* p_surfMenuOld
                            = SDL_CreateRGBSurface( 0,
                                                    p_contextUi->screen->w,
                                                    p_contextUi->screen->h,
                                                    32,
                                                    0, 0, 0, 0 );
                    SDL_BlitSurface( p_contextUi->screen,
                                     NULL,
                                     p_surfMenuOld,
                                     NULL );

                    /* Execution mode PvP */
                    ui_mode_pvp_exec( *argContextPtr );

                    /* Restauration affichage menu */
                    ui_transition( p_contextUi->screen,
                                   p_surfMenuOld,
                                   p_contextUi->screen );
                    SDL_FreeSurface( p_surfMenuOld );
                }
                    break;


                default:
                    TRACE_ERR( "Unknown item index (%d) !",
                               lCurrentChoice );
                    break;
            }
        }

    } while( ! lFlagQuit );



    /* -------------------------------------------------------------------------
     *  Nettoyage des pointeurs locaux
     */
    ui_text_delete( &txtSurvival );
    ui_text_delete( &txtExit );
    ui_text_delete( &txtPvAI );
    ui_text_delete( &txtPvP );
    ui_text_delete( &txtTitle );

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
