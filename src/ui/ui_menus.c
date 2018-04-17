#include "ui_menus.h"

#include "core/macros.h"
#include "core/TBool.h"
#include "core/TContext.h"

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

    TUiText txtArcade   = ui_text_create( "Arcade",
                                          lStyleItemDefault );

    TUiText txtPvAI     = ui_text_create( "Player Vs AI",
                                          lStyleItemDefault );

    TUiText txtPvP      = ui_text_create( "Player Vs Player",
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


    ui_text_setAlign( txtArcade, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtArcade,
                    C_SCREEN_WIDTH / 2,
                    C_SCREEN_HEIGHT / 2 );

    ui_text_setAlign( txtPvAI, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtPvAI,
                    C_SCREEN_WIDTH / 2,
                    ui_text_getRect( txtArcade ).y
                    + ui_text_getRect( txtArcade ).h * 2 );

    ui_text_setAlign( txtPvP, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtPvP,
                    C_SCREEN_WIDTH / 2,
                    ui_text_getRect( txtPvAI ).y
                    + ui_text_getRect( txtPvAI ).h * 2 );

    ui_text_setAlign( txtExit, EUiTextAlignCenter, EUiTextAlignMiddle );
    ui_text_setPos( txtExit,
                    C_SCREEN_WIDTH / 2,
                    ui_text_getRect( txtPvP ).y
                    + ui_text_getRect( txtPvP ).h * 2 );



    /* -------------------------------------------------------------------------
     *  Application des surfaces et affichage
     */
    /*
     *  Partie 1 : Fade-in titre
     */

    for( uint lAlpha = 0U ; lAlpha <= 255U ; ++lAlpha )
    {
        ui_text_setAlpha( txtTitle, lAlpha );

        ui_screenClear( *argContextPtr );
        ui_text_blit( txtTitle, p_contextUi->screen );


        if( SDL_Flip( p_contextUi->screen ) == -1 )
        {
            return EXIT_FAILURE;
        }

        SDL_Delay( 5 );
    }


    /*
     *  Partie 2 : Fade-in items menu
     */
    for( uint lAlpha = 0U ; lAlpha <= 255U ; ++lAlpha )
    {
        ui_text_setAlpha( txtArcade,    lAlpha );
        ui_text_setAlpha( txtExit,      lAlpha );
        ui_text_setAlpha( txtPvAI,      lAlpha );
        ui_text_setAlpha( txtPvP,       lAlpha );


        ui_screenClear( *argContextPtr );

        ui_text_blit( txtArcade,    p_contextUi->screen );
        ui_text_blit( txtExit,      p_contextUi->screen );
        ui_text_blit( txtPvAI,      p_contextUi->screen );
        ui_text_blit( txtPvP,       p_contextUi->screen );
        ui_text_blit( txtTitle,     p_contextUi->screen );


        if( SDL_Flip( p_contextUi->screen ) == -1 )
        {
            return EXIT_FAILURE;
        }

        SDL_Delay( 5 );
    }



    /* -------------------------------------------------------------------------
     *  Execution de la boucle de gestion des evenements
     */
    SDL_Event   lSdlEvent;
    TBool       lFlagQuit   = FALSE;

    enum EMenuItems
    {
        EMenuItemArcade = 0,
        EMenuItemPvAI,
        EMenuItemPvP,
        EMenuItemExit,

        EMenuItemsCount
    };
    int     lCurrentChoice  = EMenuItemArcade;
    TBool   lFlagChoiceOK   = FALSE;


    do
    {
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
#if 0
                case EMenuItemArcade:
                    break;
#endif

                case EMenuItemExit:
                    lFlagQuit   = TRUE;
                    break;

#if 0
                case EMenuItemPvAI:
                    break;


                case EMenuItemPvP:
                    break;
#endif


                default:
                    TRACE_ERR( "Unknown item index (%d) !",
                               lCurrentChoice );
                    break;
            }
        }


        /* Si l'utilisateur a cliqué sur le X de la fenetre */
        if( lFlagQuit )
        {
            break;
        }




        /* ---------------------------------------------------------------------
         *  Manage display
         */
        ui_text_setStyle( txtArcade,    lStyleItemDefault );
        ui_text_setStyle( txtExit,      lStyleItemDefault );
        ui_text_setStyle( txtPvAI,      lStyleItemDefault );
        ui_text_setStyle( txtPvP,       lStyleItemDefault );

        switch( lCurrentChoice )
        {
            case EMenuItemArcade:
                ui_text_setStyle( txtArcade, lStyleItemHovered );
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


        ui_screenClear( *argContextPtr );

        ui_text_blit( txtArcade,    p_contextUi->screen );
        ui_text_blit( txtExit,      p_contextUi->screen );
        ui_text_blit( txtPvAI,      p_contextUi->screen );
        ui_text_blit( txtPvP,       p_contextUi->screen );
        ui_text_blit( txtTitle,     p_contextUi->screen );


        if( SDL_Flip( p_contextUi->screen ) == -1 )
        {
            return 1;
        }


    } while( ! lFlagQuit );



    /* -------------------------------------------------------------------------
     *  Nettoyage des pointeurs locaux
     */
    ui_text_delete( &txtArcade );
    ui_text_delete( &txtExit );
    ui_text_delete( &txtPvAI );
    ui_text_delete( &txtPvP );
    ui_text_delete( &txtTitle );

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
