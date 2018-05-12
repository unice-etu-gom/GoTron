#ifndef UI_GAME_H
#define UI_GAME_H

#include <SDL/SDL.h>

#include "core/grid.h"
#include "core/TPosition2D.h"

#include "ui_text.h"


typedef enum    EPlayersID
{
    EPlayerID1  = 1,
    EPlayerID2  = 2
}   TEPlayerID;

typedef enum    EPlayerDirections
{
    EPlayerDirectionUp,
    EPlayerDirectionDown,
    EPlayerDirectionLeft,
    EPlayerDirectionRight
} TEPlayerDirection;

struct  SCurrentGame
{
    /*
     *  Data management
     */
    TCoreGrid   gridData;

    SDL_Color           player1Color;
    TPosition2D         player1Pos;
    TEPlayerDirection   player1Direction;

    SDL_Color           player2Color;
    TPosition2D         player2Pos;
    TEPlayerDirection   player2Direction;

    int                 scoreIncrement;
    int                 scorePlayer1;
    int                 scorePlayer2;



    /*
     *  Display layers
     */
    SDL_Surface*    sdl_surf_frame;
//    SDL_Surface*    sdl_surf_scores;
    SDL_Surface*    sdl_surf_gameboard;
//    SDL_Surface*    sdl_surf_playersTraces;
    SDL_Surface*    sdl_surf_playersTraceP1;
    SDL_Surface*    sdl_surf_playersTraceP2;
    SDL_Surface*    sdl_surf_player1Bike;
    SDL_Surface*    sdl_surf_player2Bike;
    TUiText         P1ScoreText;
    TUiText         P2ScoreText;

//    SDL_Surface*    sdl_surf_main;
};

typedef struct SCurrentGame*    TSCurrentGame;


#define UI_GAME_FLAG_LAYER_TRACE_P1     (0x0001)
#define UI_GAME_FLAG_LAYER_TRACE_P2     (0x0002)

#define UI_GAME_FLAG_P1                 (UI_GAME_FLAG_LAYER_TRACE_P1)
#define UI_GAME_FLAG_P2                 (UI_GAME_FLAG_LAYER_TRACE_P2)

#define UI_GAME_FLAGS_NONE              (0x0000)
#define UI_GAME_FLAG_LAYERS_ALL         (   UI_GAME_FLAG_P1 \
                                        |   UI_GAME_FLAG_P2 )

const Uint32    C_UI_GAME_FRAME_THICKNESS;
const Uint32    C_UI_GAME_TRACE_THICKNESS;



TSCurrentGame   ui_game_create( SDL_Surface *argScreenSurfacePtr,
                                SStyle argStyleScore );
void            ui_game_destroy( TSCurrentGame* argGamePtr );


int             ui_game_setPlayer1Position( TSCurrentGame argGame,
                                            int argX, int argY );
int             ui_game_setPlayer2Position( TSCurrentGame argGame,
                                            int argX, int argY );

uint    ui_game_movePlayers( TSCurrentGame argGame );


void    ui_game_setScore( TSCurrentGame argGame,
                          TEPlayerID    argPlayer,
                          int           argValue );


void    ui_game_blit( TSCurrentGame argGame,
                      SDL_Surface*  argDestSurfacePtr,
                      uint          argFlags );

void    ui_game_displayFinalScore( TSCurrentGame    argGame,
                                   SDL_Surface*     argSurfDestPtr );


#endif  /*< UI_GAME_H */
