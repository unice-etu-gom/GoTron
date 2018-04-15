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
