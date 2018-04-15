#ifndef UI_SDLTEXT_H
#define UI_SDLTEXT_H

#include "ui_styles.h"

/* ########################################################################## */
/* ########################################################################## */

typedef enum    _EUiTextAlignH
{
    EUiTextAlignLeft,
    EUiTextAlignCenter,
    EUiTextAlignRight

}   TEUiTextAlignH;


typedef enum    _EUiTextAlignV
{
    EUiTextAlignTop,
    EUiTextAlignMiddle,
    EUiTextAlignBottom

}   TEUiTextAlignV;


typedef struct _SUiTextPrivate* TUiText;

/* ########################################################################## */
/* ########################################################################## */

TUiText ui_text_create(const char* argText, SStyle argStyle);
void    ui_text_delete( TUiText* argText );



void        ui_text_setAlign( TUiText               argUiText,
                              const TEUiTextAlignH  argAlignH,
                              const TEUiTextAlignV  argAlignV );


void        ui_text_setPos( TUiText argUiText, Sint16 argPosX, Sint16 argPosY );

SDL_Rect    ui_text_getRect( TUiText argUiText );

void        ui_text_setAlpha( TUiText argUiText, uint8_t argAlpha );

void        ui_text_setStyle( TUiText argUiText, SStyle argStyle );


void        ui_text_blit(TUiText argUiText, SDL_Surface *argDestinationPtr);

/* ########################################################################## */
/* ########################################################################## */

#endif /*< UI_SDLTEXT_H */
