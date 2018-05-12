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
                              argContext.ui->style_game_scores,
                              EGameModePvP );



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
    ui_game_displayFinalScore( argContext.ui->currentGame,
                               argContext.ui->screen );


    getOut( argContext );
    TRACE_DBG( "Mode PvP ended." );
}

/* ########################################################################## */
/* ########################################################################## */
