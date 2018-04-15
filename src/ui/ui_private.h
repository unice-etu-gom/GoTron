#ifndef UI_PRIVATE_H
#define UI_PRIVATE_H

#include <SDL/SDL.h>

#include "ui_styles.h"

/* ########################################################################## */
/* ########################################################################## */

struct  _SUiContextPrivate
{
    SDL_Surface *screen;


    SDL_Color   screenBackgroundColor;


    SStyle  style_title;
};

/* ########################################################################## */
/* ########################################################################## */
/*
 * Les attributs de notre écran
 */
extern const int    C_SCREEN_WIDTH;
extern const int    C_SCREEN_HEIGHT;
extern const int    C_SCREEN_BPP;

/* ########################################################################## */
/* ########################################################################## */

void    ui_sdl_apply_surface( int x, int y,
                              SDL_Surface* source, SDL_Surface* destination,
                              SDL_Rect* clip );

/* ########################################################################## */
/* ########################################################################## */

#endif  /*< UI_PRIVATE_H */
