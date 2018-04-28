#ifndef UI_GAME_H
#define UI_GAME_H

#include <SDL/SDL.h>

#include "core/TContext.h"


struct  SCurrentGame
{
    SDL_Surface*    sdl_surf_frame;
    SDL_Surface*    sdl_surf_gameboard;
    SDL_Surface*    sdl_surf_player1Bike;
    SDL_Surface*    sdl_surf_player1Trace;
    SDL_Surface*    sdl_surf_player2Bike;
    SDL_Surface*    sdl_surf_player2Trace;
};

typedef struct SCurrentGame*    TSCurrentGame;



TSCurrentGame   ui_game_create(SDL_Surface *argScreenSurfacePtr);
void            ui_game_destroy( TSCurrentGame* argGamePtr );


void    ui_game_blit( TSCurrentGame argGame, SDL_Surface* argDestSurfacePtr );


#endif  /*< UI_GAME_H */
