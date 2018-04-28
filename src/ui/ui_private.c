#include "ui_private.h"

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
