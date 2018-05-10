#include "ui_game.h"

#include <assert.h>
#include <SDL.h>

#include "core/input.h"
#include "core/macros.h"

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

const Uint32 C_UI_GAME_FRAME_THICKNESS  = 20;
const Uint32 C_UI_GAME_TRACE_THICKNESS  = 9;

/* ########################################################################## */
/* ########################################################################## */

static void s_drawBackground(SDL_Surface* argSurf)
{
    Uint8       c_gridThikness  = 2U;
    Uint8       c_gridCellSize  = 50U;
    SDL_Color   c_gridColor     = C_SDL_COLOR_AQUA50;


    ui_surfaceFill( argSurf, C_SDL_COLOR_BLACK );


    /*
     *  Vertical lines
     */
    Uint32      lCenter = argSurf->w / 2;
    SDL_Rect    lRect;
    for(    Uint32 lOffset   = 0
        ;   lCenter + lOffset < argSurf->w
        ;   lOffset += c_gridCellSize )
    {
        lRect.h = argSurf->h;
        lRect.w = c_gridThikness;

        lRect.y = 0;

        lRect.x = lCenter + lOffset - (c_gridThikness/2);
        SDL_FillRect( argSurf, &lRect,
                      SDL_MapRGB( argSurf->format,
                                  c_gridColor.r,
                                  c_gridColor.g,
                                  c_gridColor.b ) );

        lRect.x = lCenter - lOffset - (c_gridThikness/2);
        SDL_FillRect( argSurf, &lRect,
                      SDL_MapRGB( argSurf->format,
                                  c_gridColor.r,
                                  c_gridColor.g,
                                  c_gridColor.b ) );
    }


    /*
     *  Horizontal lines
     */
    lCenter = argSurf->h / 2;
    for(    Uint32 lOffset   = 0
            ;   lCenter + lOffset /*+ c_gridCellSize*/ < argSurf->h
            ;   lOffset += c_gridCellSize )
    {
        lRect.h = c_gridThikness;
        lRect.w = argSurf->w;

        lRect.x = 0;

        lRect.y = lCenter + lOffset - (c_gridThikness/2);
        SDL_FillRect( argSurf, &lRect,
                      SDL_MapRGB( argSurf->format,
                                  c_gridColor.r,
                                  c_gridColor.g,
                                  c_gridColor.b ) );

        lRect.y = lCenter - lOffset - (c_gridThikness/2);
        SDL_FillRect( argSurf, &lRect,
                      SDL_MapRGB( argSurf->format,
                                  c_gridColor.r,
                                  c_gridColor.g,
                                  c_gridColor.b ) );
    }
}

/* ########################################################################## */
/* ########################################################################## */

TSCurrentGame   ui_game_create(SDL_Surface* argScreenSurfacePtr,
                               SStyle       argStyleScore )
{
    TSCurrentGame   retVal
            = (TSCurrentGame)malloc( sizeof( struct SCurrentGame ) );


    int     lDepth      = 32;
    Uint32  lFlags      = SDL_HWSURFACE;
    int     lGameWidth  = argScreenSurfacePtr->w * 2 / 3;
    int     lGameHeight = argScreenSurfacePtr->h * 2 / 3;
    Uint32  lMaskR      = 0;
    Uint32  lMaskG      = 0;
    Uint32  lMaskB      = 0;
    Uint32  lMaskA      = 0xFF;


    TRACE_DBG( "lGameWidth  = %d", lGameWidth );
    TRACE_DBG( "lGameHeight = %d", lGameHeight );


    retVal->player1Color    = C_SDL_COLOR_YELLOW;
    retVal->player2Color    = C_SDL_COLOR_GREEN;

    retVal->player1Direction    = EPlayerDirectionRight;
    retVal->player2Direction    = EPlayerDirectionLeft;

    retVal->scoreIncrement = 10;
    retVal->scorePlayer1   = 0;
    retVal->scorePlayer2   = 0;

    retVal->player1Pos.x        = 0;
    retVal->player1Pos.y        = lGameHeight / 2;

    retVal->player2Pos.x        = lGameWidth;
    retVal->player2Pos.y        = lGameHeight / 2;



    retVal->P1ScoreText = ui_text_create( "Player 1  : XXXXX", argStyleScore );
    ui_text_setPos( retVal->P1ScoreText,
                    5,
                    5 );

    retVal->P2ScoreText = ui_text_create( "Player 2 : XXXXX", argStyleScore );
    ui_text_setPos( retVal->P2ScoreText,
                    5,
                    5 + ui_text_getRect( retVal->P1ScoreText ).h );


    retVal->sdl_surf_frame
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth     + C_UI_GAME_FRAME_THICKNESS,
                                     lGameHeight    + C_UI_GAME_FRAME_THICKNESS,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );


    retVal->sdl_surf_gameboard
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth,
                                     lGameHeight,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );

    retVal->sdl_surf_playersTraceP1
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth,
                                     lGameHeight,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );

    retVal->sdl_surf_playersTraceP2
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth,
                                     lGameHeight,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );

    retVal->sdl_surf_player1Bike
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth,
                                     lGameHeight,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );

    retVal->sdl_surf_player2Bike
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth,
                                     lGameHeight,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );


    ui_surfaceFill( retVal->sdl_surf_frame,     C_SDL_COLOR_BLUE );
    s_drawBackground( retVal->sdl_surf_gameboard );

    ui_surfaceClear( retVal->sdl_surf_playersTraceP1);
    ui_surfaceClear( retVal->sdl_surf_playersTraceP2);
    ui_surfaceClear( retVal->sdl_surf_player1Bike );
    ui_surfaceClear( retVal->sdl_surf_player2Bike );

    retVal->gridData    = grid_create( retVal->sdl_surf_gameboard->w,
                                       retVal->sdl_surf_gameboard->h );


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_game_destroy(TSCurrentGame *argGamePtr)
{
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_frame );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_gameboard );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_playersTraceP1 );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_playersTraceP2 );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_player1Bike );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_player2Bike );
//    SDL_FreeSurface( (*argGamePtr)->sdl_surf_scores );

    ui_text_delete( &((*argGamePtr)->P1ScoreText) );
    ui_text_delete( &((*argGamePtr)->P2ScoreText) );

    grid_destroy( (*argGamePtr)->gridData );

    FREE( (*argGamePtr) );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_game_blit(   TSCurrentGame   argGame,
                        SDL_Surface*    argDestSurfacePtr,
                        uint            argFlags )
{
    assert( argGame != 0            && "argGame must be valid !" );
    assert( argDestSurfacePtr != 0  && "argDestSurfacePtr must be valid !" );
    assert( argGame->sdl_surf_gameboard->h < argDestSurfacePtr->h
            && "Height of gameboard must be smaller than destination surface!");
    assert( argGame->sdl_surf_gameboard->w < argDestSurfacePtr->w
            && "Width of gameboard must be smaller than destination surface!");


    SDL_Rect    lOffset;
    lOffset.x   = (argDestSurfacePtr->w - argGame->sdl_surf_gameboard->w) / 2;
    lOffset.y   = (argDestSurfacePtr->h - argGame->sdl_surf_gameboard->h) / 2;

    SDL_Rect    lOffsetFrame;
    lOffsetFrame.x  = lOffset.x - C_UI_GAME_FRAME_THICKNESS / 2;
    lOffsetFrame.y  = lOffset.y - C_UI_GAME_FRAME_THICKNESS / 2;




    SDL_BlitSurface( argGame->sdl_surf_frame,
                     NULL,
                     argDestSurfacePtr,
                     &lOffsetFrame );

    SDL_BlitSurface( argGame->sdl_surf_gameboard,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );
#if 0
    SDL_BlitSurface( argGame->sdl_surf_playersTraces,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );
#else
#   warning Dead code ?

    if( argFlags & UI_GAME_FLAG_LAYER_TRACE_P1 )
    {
        SDL_BlitSurface( argGame->sdl_surf_playersTraceP1,
                         NULL,
                         argDestSurfacePtr,
                         &lOffset );

    }


    if( argFlags & UI_GAME_FLAG_LAYER_TRACE_P2 )
    {
        SDL_BlitSurface( argGame->sdl_surf_playersTraceP2,
                         NULL,
                         argDestSurfacePtr,
                         &lOffset );
    }
#endif

    SDL_BlitSurface( argGame->sdl_surf_player1Bike,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );

    SDL_BlitSurface( argGame->sdl_surf_player2Bike,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );

    ui_text_blit( argGame->P1ScoreText, argDestSurfacePtr );
    ui_text_blit( argGame->P2ScoreText, argDestSurfacePtr );
}

/* ########################################################################## */
/* ########################################################################## */

static TPosition2D  s_movePlayer( TPosition2D       argCurrentPos,
                                  TEPlayerDirection argDirection )
{
    TPosition2D retVal;
    retVal.x    = argCurrentPos.x;
    retVal.y    = argCurrentPos.y;


    int lMoveOffset = C_UI_GAME_TRACE_THICKNESS;

    switch( argDirection )
    {
        case    EPlayerDirectionDown:
            retVal.y    += lMoveOffset;
            break;


        case    EPlayerDirectionLeft:
            retVal.x    -= lMoveOffset;
            break;


        case    EPlayerDirectionRight:
            retVal.x    += lMoveOffset;
            break;


        case    EPlayerDirectionUp:
            retVal.y    -= lMoveOffset;
            break;


        default:
            TRACE_ERR( "Unknown player direction of %d !",
                       argDirection );
            break;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

uint    ui_game_movePlayers(TSCurrentGame argGame)
{
    uint    retVal  = UI_GAME_FLAGS_NONE;


    /*
     *  Move players
     */
    TPosition2D lPlayer1NewPos
            = s_movePlayer( argGame->player1Pos,
                            argGame->player1Direction );

    int lPlayer1NewPosOK
            = ui_game_setPlayer1Position( argGame,
                                          lPlayer1NewPos.x,
                                          lPlayer1NewPos.y );


    TPosition2D lPlayer2NewPos
            = s_movePlayer( argGame->player2Pos,
                            argGame->player2Direction );

    int lPlayer2NewPosOK
            = ui_game_setPlayer2Position( argGame,
                                          lPlayer2NewPos.x,
                                          lPlayer2NewPos.y );



    /*
     *  Process collision detection result
     */
    if( lPlayer1NewPosOK != EXIT_SUCCESS )
    {
        TRACE_DBG( "Collision detection for player 1 !" );
        retVal  |= UI_GAME_FLAG_P1;
    }

    if( lPlayer2NewPosOK != EXIT_SUCCESS )
    {
        TRACE_DBG( "Collision detection for player 2 !" );
        retVal  |= UI_GAME_FLAG_P2;
    }

    /* Manage the case where both "trace heads" collide
     * If we don't manage this case, the losing player will be the last to be
     * moved by the game engine... */
    /* Taken from :
     * https://developer.mozilla.org/fr/docs/Games/Techniques/2D_collision_detection
     */
    if(     lPlayer1NewPos.x < lPlayer2NewPos.x + C_UI_GAME_TRACE_THICKNESS
        &&  lPlayer1NewPos.x + C_UI_GAME_TRACE_THICKNESS > lPlayer2NewPos.x
        &&  lPlayer1NewPos.y < lPlayer2NewPos.y + C_UI_GAME_TRACE_THICKNESS
        &&  lPlayer1NewPos.y + C_UI_GAME_TRACE_THICKNESS > lPlayer2NewPos.y )
    {
        TRACE_DBG( "This is a double collision !" );
        retVal  |= UI_GAME_FLAG_P1;
        retVal  |= UI_GAME_FLAG_P2;
    }


    /*
     *  Scores management
     */
    if( (retVal & UI_GAME_FLAG_P1) == 0 )
    {
        ui_game_setScore( argGame, EPlayerID1,
                          argGame->scorePlayer1 + argGame->scoreIncrement );
    }

    if( (retVal & UI_GAME_FLAG_P2) == 0 )
    {
        ui_game_setScore( argGame, EPlayerID2,
                          argGame->scorePlayer2 + argGame->scoreIncrement );
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int     ui_game_setPlayer1Position( TSCurrentGame argGame,
                                    int argX, int argY )
{
    int retVal  = EXIT_SUCCESS;


    SDL_Rect    lRect;
    lRect.w = C_UI_GAME_TRACE_THICKNESS;
    lRect.h = C_UI_GAME_TRACE_THICKNESS;
    lRect.x = argX - (C_UI_GAME_TRACE_THICKNESS / 2);
    lRect.y = argY - (C_UI_GAME_TRACE_THICKNESS / 2);


    /*
     *  Display the trace
     */
#if 0
    SDL_FillRect( argGame->sdl_surf_playersTraces,
                  &lRect,
                  SDL_MapRGB( argGame->sdl_surf_playersTraces->format,
                              argGame->player1Color.r,
                              argGame->player1Color.g,
                              argGame->player1Color.b ) );
#else
    SDL_FillRect( argGame->sdl_surf_playersTraceP1,
                  &lRect,
                  SDL_MapRGB( argGame->sdl_surf_playersTraceP1->format,
                              argGame->player1Color.r,
                              argGame->player1Color.g,
                              argGame->player1Color.b ) );
#endif


    /* SDL_FillRect modifie la taille de lRect si on atteint une bordure ;
     * de ce fait, on doit réassigner la bonne valeur au rectangle pour
     * effectuer la detection de collision. */
    lRect.w = C_UI_GAME_TRACE_THICKNESS;
    lRect.h = C_UI_GAME_TRACE_THICKNESS;



    /*
     *  Collision verification
     */
    for(    int lX = lRect.x
        ;   (lX < lRect.x + lRect.w ) && (retVal == EXIT_SUCCESS)
        ;   ++lX )
    {
        for( int lY = lRect.y ; lY < lRect.y + lRect.h ; ++lY )
        {
            if(     lX < 0
                ||  lX >= grid_columnsCount( argGame->gridData )
                ||  lY < 0
                ||  lY >= grid_rowsCount( argGame->gridData ) )
            {
                TRACE_DBG( "Player 1 came out of the gameboard at x=%u y=%u !",
                           lX, lY );
                retVal  = EXIT_FAILURE;
                break;
            }
#if 0
            else
            {
                TRACE_DBG( "0 <= x=%d < %lu",
                           lX, grid_columnsCount( argGame->gridData ) );
                TRACE_DBG( "0 <= y=%d < %lu",
                           lY, grid_rowsCount( argGame->gridData ) );
            }
#endif


            TEGridCellType lCellContent
                    = grid_getCell( argGame->gridData, lY, lX );

            if( lCellContent != EGridCellEmpty )
            {
                TRACE_DBG( "Collision from player 1 at x=%u y=%u"
                           " (content type=%c)!",
                           lX, lY,
                           grid_cellType_toChar(lCellContent) );
                retVal  = EXIT_FAILURE;
                break;
            }
            else
            {
                grid_setCell( argGame->gridData, lY, lX, EGridCellPlayer1 );
            }
        }
    }


    if( retVal == EXIT_SUCCESS )
    {
        argGame->player1Pos.x   = argX;
        argGame->player1Pos.y   = argY;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

int     ui_game_setPlayer2Position( TSCurrentGame argGame,
                                    int argX, int argY )
{
    int retVal  = EXIT_SUCCESS;


    SDL_Rect    lRect;
    lRect.w = C_UI_GAME_TRACE_THICKNESS;
    lRect.h = C_UI_GAME_TRACE_THICKNESS;
    lRect.x = argX - (C_UI_GAME_TRACE_THICKNESS / 2);
    lRect.y = argY - (C_UI_GAME_TRACE_THICKNESS / 2);


    /*
     *  Display the trace
     */
#if 0
    SDL_FillRect( argGame->sdl_surf_playersTraces,
                  &lRect,
                  SDL_MapRGB( argGame->sdl_surf_playersTraces->format,
                              argGame->player2Color.r,
                              argGame->player2Color.g,
                              argGame->player2Color.b ) );
#else
    SDL_FillRect( argGame->sdl_surf_playersTraceP2,
                  &lRect,
                  SDL_MapRGB( argGame->sdl_surf_playersTraceP2->format,
                              argGame->player2Color.r,
                              argGame->player2Color.g,
                              argGame->player2Color.b ) );
#endif


    /* SDL_FillRect modifie la taille de lRect si on atteint une bordure ;
     * de ce fait, on doit réassigner la bonne valeur au rectangle pour
     * effectuer la detection de collision. */
    lRect.w = C_UI_GAME_TRACE_THICKNESS;
    lRect.h = C_UI_GAME_TRACE_THICKNESS;



    /*
     *  Collision verification
     */
    for(    int lX = lRect.x
        ;   (lX < lRect.x + lRect.w ) && (retVal == EXIT_SUCCESS)
        ;   ++lX )
    {
        for( int lY = lRect.y ; lY < lRect.y + lRect.h ; ++lY )
        {
            if(     lX < 0
                ||  lX >= grid_columnsCount( argGame->gridData )
                ||  lY < 0
                ||  lY >= grid_rowsCount( argGame->gridData ) )
            {
                TRACE_DBG( "Player 2 came out of the gameboard at x=%u y=%u !",
                           lX, lY );
                retVal  = EXIT_FAILURE;
                break;
            }
#if 0
            else
            {
                TRACE_DBG( "0 <= x=%d < %lu",
                           lX, grid_columnsCount( argGame->gridData ) );
                TRACE_DBG( "0 <= y=%d < %lu",
                           lY, grid_rowsCount( argGame->gridData ) );
            }
#endif


            TEGridCellType lCellContent
                    = grid_getCell( argGame->gridData, lY, lX );

            if( lCellContent != EGridCellEmpty )
            {
                TRACE_DBG( "Collision from player 2 at x=%u y=%u"
                           " (content type=%c)!",
                           lX, lY,
                           grid_cellType_toChar(lCellContent) );
                retVal  = EXIT_FAILURE;
                break;
            }
            else
            {
                grid_setCell( argGame->gridData, lY, lX, EGridCellPlayer2 );
            }
        }
    }


    if( retVal == EXIT_SUCCESS )
    {
        argGame->player2Pos.x   = argX;
        argGame->player2Pos.y   = argY;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_game_setScore( TSCurrentGame argGame,
                          TEPlayerID    argPlayerID,
                          int           argValue )
{
    assert( argGame != 0 && "argGame must be valid !" );

    /*
     *  Update data
     */
    switch( argPlayerID )
    {
        case    EPlayerID1:
            argGame->scorePlayer1  = argValue;
            break;


        case    EPlayerID2:
            argGame->scorePlayer2  = argValue;
            break;


        default:
            TRACE_ERR( "Invalid player ID argument == '%d' !",
                       argPlayerID );
            break;
    }


    /*
     *  Update text
     */
    char    lBufferTmp[256] = {0};

    snprintf( lBufferTmp, 256,
              "Player 1  : %06d",
              argGame->scorePlayer1 );
    ui_text_set( argGame->P1ScoreText, lBufferTmp );

    snprintf( lBufferTmp, 256,
              "Player 2 : %06d",
              argGame->scorePlayer2 );
    ui_text_set( argGame->P2ScoreText, lBufferTmp );
}

/* ########################################################################## */
/* ########################################################################## */
