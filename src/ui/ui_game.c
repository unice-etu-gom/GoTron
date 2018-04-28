#include "ui_game.h"

#include <assert.h>
#include <SDL.h>

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

static const Uint32 C_FRAME_THICKNESS   = 20;

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
        ;   lCenter + lOffset /*+ c_gridCellSize*/ < argSurf->w
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

TSCurrentGame   ui_game_create(SDL_Surface* argScreenSurfacePtr)
{
    TSCurrentGame   retVal
            = (TSCurrentGame)malloc( sizeof( struct SCurrentGame ) );


    int     lDepth  = 32;
    Uint32  lFlags  = SDL_HWSURFACE;
    int     lGameWidth  = argScreenSurfacePtr->w * 2 / 3;
    int     lGameHeight = argScreenSurfacePtr->h * 2 / 3;
    Uint32  lMaskR  = 0;
    Uint32  lMaskG  = 0;
    Uint32  lMaskB  = 0;
    Uint32  lMaskA  = 0xFF;

    TRACE_DBG( "lGameWidth  = %d", lGameWidth );
    TRACE_DBG( "lGameHeight = %d", lGameHeight );


    retVal->sdl_surf_frame
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth     + C_FRAME_THICKNESS,
                                     lGameHeight    + C_FRAME_THICKNESS,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );


    retVal->sdl_surf_gameboard
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

    retVal->sdl_surf_player1Trace
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

    retVal->sdl_surf_player2Trace
            =  SDL_CreateRGBSurface( lFlags,
                                     lGameWidth,
                                     lGameHeight,
                                     lDepth,
                                     lMaskR, lMaskG, lMaskB, lMaskA );


    ui_surfaceFill( retVal->sdl_surf_frame,     C_SDL_COLOR_BLUE );
    s_drawBackground( retVal->sdl_surf_gameboard );
    ui_surfaceClear( retVal->sdl_surf_player1Bike );
    ui_surfaceClear( retVal->sdl_surf_player1Trace);
    ui_surfaceClear( retVal->sdl_surf_player2Bike );
    ui_surfaceClear( retVal->sdl_surf_player2Trace);


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_game_destroy(TSCurrentGame *argGamePtr)
{
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_frame );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_gameboard );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_player1Bike );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_player1Trace );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_player2Bike );
    SDL_FreeSurface( (*argGamePtr)->sdl_surf_player2Trace );

    FREE( (*argGamePtr) );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_game_blit( TSCurrentGame argGame, SDL_Surface *argDestSurfacePtr )
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
    lOffsetFrame.x  = lOffset.x - C_FRAME_THICKNESS / 2;
    lOffsetFrame.y  = lOffset.y - C_FRAME_THICKNESS / 2;



    SDL_BlitSurface( argGame->sdl_surf_frame,
                     NULL,
                     argDestSurfacePtr,
                     &lOffsetFrame );

    SDL_BlitSurface( argGame->sdl_surf_gameboard,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );

    SDL_BlitSurface( argGame->sdl_surf_player1Bike,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );

    SDL_BlitSurface( argGame->sdl_surf_player1Trace,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );

    SDL_BlitSurface( argGame->sdl_surf_player2Bike,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );

    SDL_BlitSurface( argGame->sdl_surf_player2Trace,
                     NULL,
                     argDestSurfacePtr,
                     &lOffset );
}

/* ########################################################################## */
/* ########################################################################## */
