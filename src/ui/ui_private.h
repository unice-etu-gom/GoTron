#ifndef UI_PRIVATE_H
#define UI_PRIVATE_H

#include <SDL/SDL.h>

#include "ui_game.h"
#include "ui_styles.h"

/* ########################################################################## */
/* ########################################################################## */

struct  _SUiContextPrivate
{
    SDL_Surface *screen;


    SDL_Color   screenBackgroundColor;


    SStyle  style_title;


    TSCurrentGame   currentGame;
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

void    ui_surfaceClear(SDL_Surface *argSurfacePtr);
void    ui_surfaceFill( SDL_Surface* argSurfacePtr, const SDL_Color argColor );

void    ui_sdl_apply_surface( int x, int y,
                              SDL_Surface* source, SDL_Surface* destination,
                              SDL_Rect* clip );

void    ui_transition( SDL_Surface* argOld,
                       SDL_Surface* argNew,
                       SDL_Surface* argDest );


/* ########################################################################## */
/* ########################################################################## */

#endif  /*< UI_PRIVATE_H */
