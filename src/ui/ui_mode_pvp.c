#include "ui_mode_pvp.h"

#include <SDL.h>

#include "core/input.h"
#include "core/TBool.h"

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

static void getIn( TContext argContext )
{
    /*
     *  Initialize data
     */
    argContext.ui->currentGame
            = ui_game_create( argContext.ui->screen,
                              argContext.ui->style_game_scores );



    /*
     *  Manage UI creation and transition
     */
    SDL_Surface*    p_surf_tmpGame
            = SDL_CreateRGBSurface( 0,
                                    argContext.ui->screen->w,
                                    argContext.ui->screen->h,
                                    32,
                                    0, 0, 0, 0 );
    ui_game_blit( argContext.ui->currentGame,
                  p_surf_tmpGame,
                  UI_GAME_FLAGS_NONE );


    ui_transition( argContext.ui->screen,
                   p_surf_tmpGame,
                   argContext.ui->screen );



    ui_game_setPlayer1Position(
                argContext.ui->currentGame,
                C_UI_GAME_TRACE_THICKNESS / 2,
                argContext.ui->currentGame->sdl_surf_gameboard->h / 2 );

    ui_game_blit( argContext.ui->currentGame,
                  argContext.ui->screen,
                  UI_GAME_FLAG_LAYERS_ALL );
    SDL_Flip( argContext.ui->screen );


//    ui_game_countdown()


    /* Flush events buffer */
    while( input_keyboardEvent_poll() != SDLK_UNKNOWN );
}

/* ########################################################################## */
/* ########################################################################## */

static void getOut( TContext argContext )
{
    ui_game_destroy( &(argContext.ui->currentGame) );
}

/* ########################################################################## */
/* ########################################################################## */

static void s_ui_mode_pvp_readKeyboardInputs(TSCurrentGame argGame)
{
    SDLKey  lKey    = SDLK_UNKNOWN;


    /* Poll for events */
    while( (lKey=input_keyboardEvent_poll()) != SDLK_UNKNOWN )
    {
        /* Passage des minuscules en majuscules */
        if( lKey >= 'a' && lKey <= 'z' )
        {
            lKey    -= 'a' - 'A';
        }


        switch( lKey )
        {
            case    'Z':
                if( argGame->player1Direction != EPlayerDirectionDown )
                {
                    argGame->player1Direction   = EPlayerDirectionUp;
                }
                break;


            case    'Q':
                if( argGame->player1Direction != EPlayerDirectionRight )
                {
                    argGame->player1Direction   = EPlayerDirectionLeft;
                }
                break;


            case    'S':
                if( argGame->player1Direction != EPlayerDirectionUp )
                {
                    argGame->player1Direction   = EPlayerDirectionDown;
                }
                break;


            case    'D':
                if( argGame->player1Direction != EPlayerDirectionLeft )
                {
                    argGame->player1Direction   = EPlayerDirectionRight;
                }
                break;


            case    SDLK_UP:
                if( argGame->player2Direction != EPlayerDirectionDown )
                {
                    argGame->player2Direction   = EPlayerDirectionUp;
                }
                break;


            case    SDLK_LEFT:
                if( argGame->player2Direction != EPlayerDirectionRight )
                {
                    argGame->player2Direction   = EPlayerDirectionLeft;
                }
                break;


            case    SDLK_DOWN:
                TRACE_DBG( "Player 2 direction : Down" );
                if( argGame->player2Direction != EPlayerDirectionUp )
                {
                    argGame->player2Direction   = EPlayerDirectionDown;
                }
                break;


            case    SDLK_RIGHT:
                if( argGame->player2Direction != EPlayerDirectionLeft )
                {
                    argGame->player2Direction   = EPlayerDirectionRight;
                }
                break;


            default:
                TRACE_DBG( "Unknown key :" );

                break;
        }
    }
}

/* ########################################################################## */
/* ########################################################################## */

int ui_mode_pvp_exec(TContext argContext)
{
    TRACE_DBG( "Mode PvP started." );

    getIn( argContext );


    /* -------------------------------------------------------------------------
     *  Game management
     */

    /** Cette variable contient le resultat du déplacement des joueurs ; en cas
     * de collision, la fonction de déplacement retourne des flags identifiant
     * les joueurs en collision. */
    int     lMoveResultFlags    = 0;

    do
    {
        s_ui_mode_pvp_readKeyboardInputs( argContext.ui->currentGame );
        lMoveResultFlags    = ui_game_movePlayers( argContext.ui->currentGame );


        /*
         *  Update display
         */
        ui_surfaceClear( argContext.ui->screen );
        ui_game_blit( argContext.ui->currentGame,
                      argContext.ui->screen,
                      UI_GAME_FLAG_LAYERS_ALL );

        if( SDL_Flip( argContext.ui->screen ) == -1 )
        {
            TRACE_ERR( "SDL_Flip failure." );
        }

        SDL_Delay( 50 );
    } while( lMoveResultFlags == UI_GAME_FLAGS_NONE );


    /*
     *  End of game
     */
    /* Let the trace of the losing player(s) blink */
    uint    lFlagsAll       = UI_GAME_FLAG_LAYERS_ALL;
    uint    lFlagsNoLosers  = UI_GAME_FLAG_LAYERS_ALL &~(lMoveResultFlags);

    for( int lBlinkCount = 0 ; lBlinkCount < 8 ; ++lBlinkCount )
    {
        uint    lFlags  = lBlinkCount %2 ?
                                lFlagsAll
                            :   lFlagsNoLosers;


        ui_game_blit( argContext.ui->currentGame,
                      argContext.ui->screen,
                      lFlags );

        if( SDL_Flip( argContext.ui->screen ) == -1 )
        {
            TRACE_ERR( "SDL_Flip failure." );
        }

        SDL_Delay( 300 );
    }


    /*
     *  Display the score
     */
    SDLKey      lKey    = SDLK_UNKNOWN;
    SDL_Rect    lOffset;
    SDL_Surface* p_sdlSurf_oldScreen
            = SDL_CreateRGBSurface( 0,
                                    argContext.ui->screen->w,
                                    argContext.ui->screen->h,
                                    32,
                                    0, 0, 0, 0 );
    ui_surfaceFill( p_sdlSurf_oldScreen, C_SDL_COLOR_BLACK );
    SDL_BlitSurface( argContext.ui->screen, NULL,
                     p_sdlSurf_oldScreen, NULL );


    SStyle  lTitleStyle;
    ui_style_create( &lTitleStyle, C_FONT_CONST1, 40, C_SDL_COLOR_BLACK );

    TUiText lTitleText   = ui_text_create( "text", lTitleStyle );
    ui_text_setAlign( lTitleText, EUiTextAlignMiddle, EUiTextAlignBottom );


    SStyle  lTextStyle;
    ui_style_create( &lTextStyle, C_FONT_CONST1, 16, C_SDL_COLOR_BLACK );

    TUiText lTextText   = ui_text_create( "<Press any key to continue>",
                                           lTextStyle );
    ui_text_setAlign( lTextText, EUiTextAlignMiddle, EUiTextAlignBottom );



    SDL_Color   lBackgroundColor    = C_SDL_COLOR_WHITE;

    /*
     *  Conditional formatting
     */
    if(     argContext.ui->currentGame->scorePlayer1
        >   argContext.ui->currentGame->scorePlayer2 )
    {
        ui_text_set( lTitleText, "Player 1 won the game !" );
        lBackgroundColor    = argContext.ui->currentGame->player1Color;
    }
    else if(    argContext.ui->currentGame->scorePlayer1
            <   argContext.ui->currentGame->scorePlayer2 )
    {
        ui_text_set( lTitleText, "Player 2 won the game !" );
        lBackgroundColor    = argContext.ui->currentGame->player2Color;
    }
    else
    {
        ui_text_set( lTitleText, "YOU BOTH ARE LOOOSEEERS !!!" );
        lBackgroundColor    = C_SDL_COLOR_RED;
    }



    /* Flush events buffer */
    while( input_keyboardEvent_poll() != SDLK_UNKNOWN );

    const int c_marginSize = 5;
    SDL_Surface* p_sdlSurf_result
            = SDL_CreateRGBSurface( 0,
                                    c_marginSize * 2
                                    + ui_text_getRect( lTitleText ).w
                                    + c_marginSize * 2,
                                    c_marginSize
                                    + ui_text_getRect( lTitleText ).h
                                    + c_marginSize
                                    + ui_text_getRect( lTextText).h
                                    + c_marginSize,
                                    32,
                                    0, 0, 0, 0 );
    ui_surfaceFill( p_sdlSurf_result, lBackgroundColor );
    lOffset.x   = c_marginSize;
    lOffset.y   = c_marginSize;
    lOffset.w   = p_sdlSurf_result->w - (c_marginSize * 2);
    lOffset.h   = p_sdlSurf_result->h - (c_marginSize * 2);
    SDL_FillRect( p_sdlSurf_result,
                  &lOffset,
                  SDL_MapRGB( p_sdlSurf_result->format,
                              C_SDL_COLOR_WHITE.r,
                              C_SDL_COLOR_WHITE.g,
                              C_SDL_COLOR_WHITE.b ) );

    ui_text_setPos( lTitleText,
                    p_sdlSurf_result->w / 2,
                    c_marginSize );

    ui_text_setPos( lTextText,
                    p_sdlSurf_result->w / 2,
                    c_marginSize
                    + ui_text_getRect( lTitleText ).h
                    + c_marginSize );


    ui_text_blit( lTitleText,   p_sdlSurf_result );


    lOffset.x   = (argContext.ui->screen->w - p_sdlSurf_result->w ) / 2;
    lOffset.y   = (argContext.ui->screen->h - p_sdlSurf_result->h ) / 2;
    lOffset.w   = 0;
    lOffset.h   = 0;





    SDL_Surface* p_sdlSurf_newScreen
            = SDL_CreateRGBSurface( 0,
                                    argContext.ui->screen->w,
                                    argContext.ui->screen->h,
                                    32,
                                    0, 0, 0, 0 );
    ui_surfaceFill( p_sdlSurf_newScreen, lBackgroundColor );
    ui_text_blit( argContext.ui->currentGame->P1ScoreText,
                  p_sdlSurf_newScreen );
    ui_text_blit( argContext.ui->currentGame->P2ScoreText,
                  p_sdlSurf_newScreen );
//    SDL_BlitSurface( argContext.ui->screen, NULL,
//                     p_sdlSurf_newScreen, NULL );
    SDL_BlitSurface( p_sdlSurf_result, NULL,
                     p_sdlSurf_newScreen, &lOffset );



    ui_transitionIn( p_sdlSurf_oldScreen,
                     p_sdlSurf_newScreen,
                     argContext.ui->screen );



    ui_text_blit( lTextText, p_sdlSurf_result );
    SDL_BlitSurface( p_sdlSurf_result, NULL,
                     argContext.ui->screen, &lOffset );
    SDL_Flip( argContext.ui->screen );


    while( (lKey=input_keyboardEvent_poll()) == SDLK_UNKNOWN );


    SDL_FreeSurface( p_sdlSurf_result );


    getOut( argContext );
    TRACE_DBG( "Mode PvP ended." );
}

/* ########################################################################## */
/* ########################################################################## */
