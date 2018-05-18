#include "ui_mode_survival.h"

#include <assert.h>

#include <SDL.h>

#include "core/input.h"
#include "core/TBool.h"
#include "core/data/highscores.h"

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

static void s_ui_mode_survival_displayFinalScore(TSCurrentGame  argGame,
                                                 SDL_Surface*   argSurfDestPtr);

/* ########################################################################## */
/* ########################################################################## */

void    s_registerHighScore( TUiContext         argContext,
                             int                argScore,
                             THighscoresList*   argListPtr )
{
    char    lBuffer[16]     = {0};
    size_t  lCharIdx        = 0;
    int     lDepth          = 32;
    Uint32  lFlags          = SDL_HWSURFACE;
    TBool   lLoopContinue   = TRUE;
    Uint32  lMaskR          = 0;
    Uint32  lMaskG          = 0;
    Uint32  lMaskB          = 0;
    Uint32  lMaskA          = 0xFF;


    SDL_Surface* p_surf_base
            =  SDL_CreateRGBSurface( lFlags,
                                     argContext->screen->w,
                                     argContext->screen->h,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );

    SStyle lStyleTitre;
    ui_style_create( &lStyleTitre, C_FONT_TRON, 40, C_SDL_COLOR_YELLOW );

    TUiText lTextTitle  = ui_text_create( "New High Score !",
                                          lStyleTitre );
    TUiText lTextStatic = ui_text_create( "Please enter your nickname :",
                                          argContext->style_game_scores );

    TUiText lTextInput  = ui_text_create( "________",
                                          argContext->style_game_scores );

    ui_text_setPos( lTextTitle,
                    argContext->screen->w / 2,
                    argContext->screen->h / 4 );

    ui_text_setPos( lTextStatic,
                    argContext->screen->w / 2,
                    argContext->screen->h / 2 - ui_text_getRect(lTextStatic).h);

    ui_text_setPos( lTextInput,
                    argContext->screen->w / 2,
                    argContext->screen->h / 2 + ui_text_getRect(lTextInput).h);

    ui_text_setAlign( lTextTitle,   EUiTextAlignMiddle, EUiTextAlignCenter );
    ui_text_setAlign( lTextStatic,  EUiTextAlignMiddle, EUiTextAlignCenter );
    ui_text_setAlign( lTextInput,   EUiTextAlignMiddle, EUiTextAlignCenter );


    /*
     *  Manage a transition
     */
    /* Create a copy of the old screen */
    SDL_Surface* p_sdlSurf_oldScreen
            = SDL_CreateRGBSurface( 0,
                                    argContext->screen->w,
                                    argContext->screen->h,
                                    32,
                                    0, 0, 0, 0 );
    ui_surfaceFill( p_sdlSurf_oldScreen, C_SDL_COLOR_BLACK );
    SDL_BlitSurface( argContext->screen, NULL,
                     p_sdlSurf_oldScreen, NULL );

    /* Create a temporary display of the new screen */
    /* Update text object */
    char    lTextBuff[9]   = {0};
    strncpy( lTextBuff, lBuffer, 9 );

    size_t  lTmpIdx = strlen( lTextBuff );
    while( lTmpIdx < 8 )
    {
        lTextBuff[ lTmpIdx ]    = '_';
        lTmpIdx++;
    }
    lTextBuff[ lTmpIdx ]    = '\0';

    ui_text_set( lTextInput, lTextBuff );

    /* Update display */
    ui_surfaceFill( p_surf_base, C_SDL_COLOR_BLACK );
    ui_text_blit( lTextTitle,   p_surf_base );
    ui_text_blit( lTextStatic,  p_surf_base );
    ui_text_blit( lTextInput,   p_surf_base );


    /* Proceed the transition */
    ui_transitionIn( p_sdlSurf_oldScreen,
                     p_surf_base,
                     argContext->screen );


    /*
     *  Ask player's pseudo
     */
    do
    {
        /* Update text object */
        char    lTextBuff[9]   = {0};
        strncpy( lTextBuff, lBuffer, 9 );

        size_t  lTmpIdx = strlen( lTextBuff );
        while( lTmpIdx < 8 )
        {
            lTextBuff[ lTmpIdx ]    = '_';
            lTmpIdx++;
        }
        lTextBuff[ lTmpIdx ]    = '\0';

        ui_text_set( lTextInput, lTextBuff );

        /* Update display */
        ui_surfaceFill( p_surf_base, C_SDL_COLOR_BLACK );
        ui_text_blit( lTextTitle,   p_surf_base );
        ui_text_blit( lTextStatic,  p_surf_base );
        ui_text_blit( lTextInput,   p_surf_base );

        SDL_BlitSurface( p_surf_base, NULL, argContext->screen, NULL );
        SDL_Flip( argContext->screen );


        /* Get user input */
        SDLKey  lKey    = input_keyboardEvent_poll();

        /* Proceed actions depending on input */
        if( lKey == SDLK_RETURN )
        {
            /* End of loop */
            lLoopContinue   = FALSE;
        }
        else if( lKey == SDLK_BACKSPACE )
        {
            if ( lCharIdx > 0 )
            {
                lCharIdx--;
                lBuffer[ lCharIdx ]  = '\0';
            }
        }
        else if(    SDLK_a <= lKey  &&  lKey <= SDLK_z )
        {
//            ajouter le char dans le buffer
            if( lCharIdx < 8 )
            {
                lBuffer[lCharIdx]   = (char)lKey + 'A'-'a';
                TRACE_DBG( "Char valide : %c", lBuffer[lCharIdx] );
                lCharIdx++;
            }
        }

        SDL_Delay( 20 );
    } while( lLoopContinue );

    if( lBuffer[ 0 ] == '\0' )
    {
        lBuffer[ 0 ]    = '?';
        lBuffer[ 1 ]    = '?';
        lBuffer[ 2 ]    = '?';
        lBuffer[ 3 ]    = '\0';
    }


    THighscoresListElt  p_elt   = highscoreElt_create( lBuffer, argScore );
    highscoresList_insertEltOrdered( argListPtr, p_elt );
    highscoresList_save( *argListPtr );



    /* Release local resources */
    SDL_FreeSurface( p_surf_base );
    ui_text_delete( &lTextInput );
    ui_text_delete( &lTextStatic );
    ui_text_delete( &lTextTitle );
}

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
                              EGameModeSurvie );



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
    input_flushPendingEvents();
}

/* ########################################################################## */
/* ########################################################################## */

static void getOut( TContext argContext )
{
    ui_game_destroy( &(argContext.ui->currentGame) );
}

/* ########################################################################## */
/* ########################################################################## */

void    s_ui_mode_survival_displayFinalScore( TSCurrentGame argGame,
                                              SDL_Surface*  argSurfDestPtr )
{
    assert( argGame != NULL         && "argGame must be valid !" );
    assert( argSurfDestPtr != NULL  && "argSurfDestPtr must be valid !" );


    const int       c_marginSize        = 5;

    SDL_Color       lBackgroundColor    = C_SDL_COLOR_BLACK;
    SDLKey          lKey                = SDLK_UNKNOWN;
    SDL_Rect        lOffset             = {0};
    char            lStrBufferTmp[80]   = {0};
    SStyle          lStyleParagraph     = NULL;
    SStyle          lStyleScores        = NULL;
    SStyle          lStyleTitle         = NULL;
    TUiText         lTextPressAKey      = NULL;
    TUiText         lTextScore          = NULL;
    TUiText         lTitleText          = NULL;
    SDL_Surface*    p_sdlSurf_newScreen = NULL;
    SDL_Surface*    p_sdlSurf_oldScreen = NULL;
//    SDL_Surface*    p_sdlSurf_newScreen    = NULL;

    TUiText lTextHSIDs[C_HIGHSCORES_MAXCOUNT];
    TUiText lTextHSPseudos[C_HIGHSCORES_MAXCOUNT];
    TUiText lTextHSScores[C_HIGHSCORES_MAXCOUNT];


    p_sdlSurf_oldScreen
            = SDL_CreateRGBSurface( 0,
                                    argSurfDestPtr->w,
                                    argSurfDestPtr->h,
                                    32,
                                    0, 0, 0, 0 );
    ui_surfaceFill( p_sdlSurf_oldScreen, C_SDL_COLOR_BLACK );
    SDL_BlitSurface( argSurfDestPtr, NULL,
                     p_sdlSurf_oldScreen, NULL );



    ui_style_create( &lStyleParagraph, C_FONT_CONST1, 16, C_SDL_COLOR_RED );
    ui_style_create( &lStyleScores, C_FONT_TRON,    20, C_SDL_COLOR_YELLOW );
    ui_style_create( &lStyleTitle,  C_FONT_TRON,    40, C_SDL_COLOR_PINK );

    lTitleText  = ui_text_create( "End of game !", lStyleTitle );
    ui_text_setAlign( lTitleText, EUiTextAlignMiddle, EUiTextAlignBottom );


    int lPosY       = argSurfDestPtr->h / 2;
    int lTmpCount   = 0;

    THighscoresListElt  lEltIterator    = argGame->highscores;
    while(      lEltIterator != NULL
            &&  lTmpCount < C_HIGHSCORES_MAXCOUNT )
    {
        snprintf( lStrBufferTmp, 80,
                  "%d",
                  lTmpCount+1 );
        lTextHSIDs[ lTmpCount ] = ui_text_create( lStrBufferTmp, lStyleScores );

        lTextHSPseudos[ lTmpCount ] = ui_text_create( lEltIterator->data.pseudo,
                                                      lStyleScores );

        snprintf( lStrBufferTmp, 80,
                  "%d",
                  lEltIterator->data.score );
        lTextHSScores[ lTmpCount ]  = ui_text_create( lStrBufferTmp,
                                                      lStyleScores );

        ui_text_setPos( lTextHSIDs[ lTmpCount ],
                        argSurfDestPtr->w / 3,
                        lPosY );

        ui_text_setPos( lTextHSPseudos[ lTmpCount ],
                        argSurfDestPtr->w / 2,
                        lPosY );

        ui_text_setPos( lTextHSScores[ lTmpCount ],
                        (argSurfDestPtr->w / 3) * 2,
                        lPosY );


        ui_text_setAlign( lTextHSIDs[ lTmpCount ],
                          EUiTextAlignMiddle, EUiTextAlignBottom);

        ui_text_setAlign( lTextHSPseudos[ lTmpCount ],
                          EUiTextAlignMiddle, EUiTextAlignBottom);

        ui_text_setAlign( lTextHSScores[ lTmpCount ],
                          EUiTextAlignRight, EUiTextAlignBottom);


        lPosY   += ui_text_getRect( lTextHSIDs[ lTmpCount ] ).h;

        lTmpCount++;
        lEltIterator    = lEltIterator->next;
    }


    for( int i = lTmpCount ; i < C_HIGHSCORES_MAXCOUNT ; i++ )
    {
        snprintf( lStrBufferTmp, 80,
                  "%d",
                  i+1 );
        lTextHSIDs[ i ] = ui_text_create( lStrBufferTmp, lStyleScores );

        lTextHSPseudos[ i ] = ui_text_create( "________", lStyleScores );
        lTextHSScores[ i ]  = ui_text_create( "???", lStyleScores );

        ui_text_setPos( lTextHSIDs[ i ],
                        argSurfDestPtr->w / 3,
                        lPosY );

        ui_text_setPos( lTextHSPseudos[ i ],
                        argSurfDestPtr->w / 2,
                        lPosY );

        ui_text_setAlign( lTextHSIDs[ i ],
                          EUiTextAlignMiddle,
                          EUiTextAlignBottom );

        ui_text_setAlign( lTextHSPseudos[ i ],
                          EUiTextAlignCenter,
                          EUiTextAlignBottom );

        ui_text_setAlign( lTextHSScores[ i ],
                          EUiTextAlignRight,
                          EUiTextAlignBottom );

        lPosY   += ui_text_getRect( lTextHSIDs[ i ] ).h;
    }



    lTextPressAKey  = ui_text_create( "<Press any key to continue>",
                                      lStyleParagraph );
    lTextScore  = ui_text_create( "tmp", lStyleParagraph );

    ui_text_setAlign( lTextScore,       EUiTextAlignMiddle, EUiTextAlignBottom);
    ui_text_setAlign( lTextPressAKey,   EUiTextAlignMiddle, EUiTextAlignBottom);


    /*
     *  Specific text
     */
    snprintf( lStrBufferTmp, 80,
              "Final score : %d",
              argGame->scorePlayer1 );
    ui_text_set( lTextScore, lStrBufferTmp );






    /* Flush events buffer */
    input_flushPendingEvents();


    p_sdlSurf_newScreen
            = SDL_CreateRGBSurface( 0,
                                    argSurfDestPtr->w,
                                    argSurfDestPtr->h,
                                    32,
                                    0, 0, 0, 0 );
    ui_surfaceFill( p_sdlSurf_newScreen, lBackgroundColor );
    lOffset.x   = c_marginSize;
    lOffset.y   = c_marginSize;
    lOffset.w   = p_sdlSurf_newScreen->w - (c_marginSize * 2);
    lOffset.h   = p_sdlSurf_newScreen->h - (c_marginSize * 2);
//    SDL_FillRect( p_sdlSurf_newScreen,
//                  &lOffset,
//                  SDL_MapRGB( p_sdlSurf_newScreen->format,
//                              lBackgroundColor.r,
//                              lBackgroundColor.g,
//                              lBackgroundColor.b ) );

    int lOffsetH    = p_sdlSurf_newScreen->h / 4;
    ui_text_setPos( lTitleText,
                    p_sdlSurf_newScreen->w / 2,
                    lOffsetH );
    ui_text_blit( lTitleText,   p_sdlSurf_newScreen );

    lOffsetH    += ui_text_getRect( lTitleText ).h;
    lOffsetH    += c_marginSize;
    ui_text_setPos( lTextScore,
                    p_sdlSurf_newScreen->w / 2,
                    lOffsetH );
    ui_text_blit( lTextScore,   p_sdlSurf_newScreen );


    lOffsetH    += ui_text_getRect( lTextScore ).h;
    lOffsetH    += c_marginSize;
    ui_text_setPos( lTextPressAKey,
                    p_sdlSurf_newScreen->w / 2,
                    p_sdlSurf_newScreen->h
                    - (c_marginSize * 2)
                    - ui_text_getRect(lTextPressAKey).h );


    lOffset.x   = (argSurfDestPtr->w - p_sdlSurf_newScreen->w ) / 2;
    lOffset.y   = (argSurfDestPtr->h - p_sdlSurf_newScreen->h ) / 3;
    lOffset.w   = 0;
    lOffset.h   = 0;





    for( int i = 0 ; i < C_HIGHSCORES_MAXCOUNT ; i++ )
    {
        ui_text_blit( lTextHSIDs[ i ],      p_sdlSurf_newScreen );
        ui_text_blit( lTextHSPseudos[ i ],  p_sdlSurf_newScreen );
        ui_text_blit( lTextHSScores[ i ],   p_sdlSurf_newScreen );
    }



    ui_transitionIn( p_sdlSurf_oldScreen,
                     p_sdlSurf_newScreen,
                     argSurfDestPtr );



    ui_text_blit( lTextPressAKey, p_sdlSurf_newScreen );
    SDL_BlitSurface( p_sdlSurf_newScreen, NULL,
                     argSurfDestPtr, &lOffset );
    SDL_Flip( argSurfDestPtr );


    while( (lKey=input_keyboardEvent_poll()) == SDLK_UNKNOWN )
    {
        SDL_Delay( 20 );
    }


    SDL_FreeSurface( p_sdlSurf_newScreen );
}

/* ########################################################################## */
/* ########################################################################## */

static void s_ui_mode_survival_readKeyboardInputs(TSCurrentGame argGame)
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
            case    SDLK_UP:
                if( argGame->player1Direction != EPlayerDirectionDown )
                {
                    argGame->player1Direction   = EPlayerDirectionUp;
                }
                break;


            case    SDLK_LEFT:
                if( argGame->player1Direction != EPlayerDirectionRight )
                {
                    argGame->player1Direction   = EPlayerDirectionLeft;
                }
                break;


            case    SDLK_DOWN:
                if( argGame->player1Direction != EPlayerDirectionUp )
                {
                    argGame->player1Direction   = EPlayerDirectionDown;
                }
                break;


            case    SDLK_RIGHT:
                if( argGame->player1Direction != EPlayerDirectionLeft )
                {
                    argGame->player1Direction   = EPlayerDirectionRight;
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

int ui_mode_survival_exec(TContext argContext)
{
    TRACE_DBG( "Mode Survival started." );

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
        s_ui_mode_survival_readKeyboardInputs( argContext.ui->currentGame );
        lMoveResultFlags    = ui_game_movePlayers( argContext.ui->currentGame );


        /*
         *  Update display
         */
        ui_surfaceClear( argContext.ui->screen );
        ui_game_blit( argContext.ui->currentGame,
                      argContext.ui->screen,
                      UI_GAME_FLAG_LAYERS_ALL & ~(UI_GAME_FLAG_P2) );

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
    uint    lFlagsAll       = UI_GAME_FLAG_LAYERS_ALL &~(UI_GAME_FLAG_P2);
    uint    lFlagsNoLosers  = lFlagsAll &~(lMoveResultFlags);

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
    TBool   lNewHighScore
            = highscoresList_checkIfAccepted(
                  argContext.ui->currentGame->highscores,
                  argContext.ui->currentGame->scorePlayer1 );

    if( lNewHighScore )
    {
        TRACE_DBG( "New high score detected." );
        s_registerHighScore( argContext.ui,
                             argContext.ui->currentGame->scorePlayer1,
                             &argContext.ui->currentGame->highscores );
    }

    s_ui_mode_survival_displayFinalScore( argContext.ui->currentGame,
                                          argContext.ui->screen );


    getOut( argContext );
    TRACE_DBG( "Mode Survival ended." );
}

/* ########################################################################## */
/* ########################################################################## */

