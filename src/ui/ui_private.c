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

const int   C_SCREEN_WIDTH  = 800;
const int   C_SCREEN_HEIGHT = 600;
const int   C_SCREEN_BPP    = 32;

/* ########################################################################## */
/* ########################################################################## */

void    ui_sdl_apply_surface( int x, int y,
                              SDL_Surface* source, SDL_Surface* destination,
                              SDL_Rect* clip )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    /* On blitte la surface */
    SDL_BlitSurface( source, clip, destination, &offset );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_surfaceClear(SDL_Surface *argSurfacePtr)
{
    ui_surfaceFill( argSurfacePtr, C_SDL_COLOR_BLACK );
    SDL_SetColorKey( argSurfacePtr,
                     SDL_SRCCOLORKEY,
                     SDL_MapRGB(argSurfacePtr->format, 0, 0, 0 ) );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_surfaceFill(SDL_Surface *argSurfacePtr, const SDL_Color argColor)
{
    SDL_FillRect( argSurfacePtr,
                  NULL,
                  SDL_MapRGB( argSurfacePtr->format,
                              argColor.r,
                              argColor.g,
                              argColor.b ) );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_transitionIn( SDL_Surface* argOld,
                         SDL_Surface* argNew,
                         SDL_Surface* argDest )
{
    SDL_Color   lContourColor   = C_SDL_COLOR_AQUA50;

    SDL_Surface* p_surfCadre
            = SDL_CreateRGBSurface( 0,
                                    argDest->w,
                                    argDest->h,
                                    32,
                                    0, 0, 0, 0 );


    for( int lPercent = 100 ; lPercent > 1 ; lPercent-- )
    {
        SDL_Rect lRect;
        lRect.w = argDest->w * lPercent / 100;
        lRect.h = argDest->h * lPercent / 100;
        lRect.x = argDest->w / 2    - lRect.w / 2;
        lRect.y = argDest->h / 2    - lRect.h / 2;


        /* Le contour est plus grand que le centre de 4px pour avoir une bordure
         * de 2px */

        SDL_Rect    lContourRect    = lRect;
        lContourRect.w  += 4;
        lContourRect.h  += 4;
        lContourRect.x  -= 2;
        lContourRect.y  -= 2;


        /* Dessin du carré du contour */
        ui_surfaceClear( p_surfCadre );
        SDL_FillRect( p_surfCadre,
                      &lContourRect,
                      SDL_MapRGB( p_surfCadre->format,
                                  lContourColor.r,
                                  lContourColor.g,
                                  lContourColor.b ) );

        /* Remplissage de l'interieur */
        SDL_BlitSurface( argNew, NULL, argDest, NULL );
        SDL_BlitSurface( p_surfCadre, NULL, argDest, NULL );
        SDL_BlitSurface( argOld, &lRect, argDest, &lRect );


        if( SDL_Flip( argDest ) == -1 )
        {
            TRACE_ERR( "SDL_Flip failure." );
            return;
        }

        SDL_Delay( 10 );
    }


    /* This last blit is made to be shure we won't have any remanent element of
     * the old surface into the new one. */
    ui_surfaceClear( argDest );
    SDL_BlitSurface( argNew, NULL, argDest, NULL );
    if( SDL_Flip( argDest ) == -1 )
    {
        TRACE_ERR( "SDL_Flip failure." );
        return;
    }


    SDL_FreeSurface( p_surfCadre );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_transition( SDL_Surface* argOld,
                       SDL_Surface* argNew,
                       SDL_Surface* argDest )
{
    SDL_Color   lContourColor   = C_SDL_COLOR_RED;

    SDL_Surface* p_surfCadre
            = SDL_CreateRGBSurface( 0,
                                    argDest->w,
                                    argDest->h,
                                    32,
                                    0, 0, 0, 0 );


    for( int lPercent = 1 ; lPercent < 100 ; lPercent++ )
    {
        SDL_Rect lRect;
        lRect.w = argDest->w * lPercent / 100;
        lRect.h = argDest->h * lPercent / 100;
        lRect.x = argDest->w / 2    - lRect.w / 2;
        lRect.y = argDest->h / 2    - lRect.h / 2;


        /* Le contour est plus grand que le centre de 4px pour avoir une bordure
         * de 2px */

        SDL_Rect    lContourRect    = lRect;
        lContourRect.w  += 4;
        lContourRect.h  += 4;
        lContourRect.x  -= 2;
        lContourRect.y  -= 2;


        /* Dessin du carré du contour */
        ui_surfaceClear( p_surfCadre );
        SDL_FillRect( p_surfCadre,
                      &lContourRect,
                      SDL_MapRGB( p_surfCadre->format,
                                  lContourColor.r,
                                  lContourColor.g,
                                  lContourColor.b ) );

        /* Remplissage de l'interieur */
        SDL_BlitSurface( argOld, NULL, argDest, NULL );
        SDL_BlitSurface( p_surfCadre, NULL, argDest, NULL );
        SDL_BlitSurface( argNew, &lRect, argDest, &lRect );


        if( SDL_Flip( argDest ) == -1 )
        {
            TRACE_ERR( "SDL_Flip failure." );
            return;
        }

        SDL_Delay( 10 );
    }


    /* This last blit is made to be shure we won't have any remanent element of
     * the old surface into the new one. */
    ui_surfaceClear( argDest );
    SDL_BlitSurface( argNew, NULL, argDest, NULL );
    if( SDL_Flip( argDest ) == -1 )
    {
        TRACE_ERR( "SDL_Flip failure." );
        return;
    }


    SDL_FreeSurface( p_surfCadre );
}

/* ########################################################################## */
/* ########################################################################## */
