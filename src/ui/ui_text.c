#include "ui_text.h"

#include <SDL_ttf.h>
#include <SDL/SDL_video.h>

#include "core/macros.h"

#include "ui_styles.h"

/* ########################################################################## */
/* ########################################################################## */

struct  _SUiTextPrivate
{
    char*           text;

    SStyle          stylePtr;
    uint8_t         alpha;
    Sint16          posX;
    Sint16          posY;
    TEUiTextAlignH  alignH;
    TEUiTextAlignV  alignV;

    SDL_Surface*    sdl_surface;
};

/* ########################################################################## */
/* ########################################################################## */

static void s_updateSurface(TUiText argUiText)
{
    if( argUiText->sdl_surface )
    {
        SDL_FreeSurface( argUiText->sdl_surface );
    }


    argUiText->sdl_surface
            = TTF_RenderText_Solid(
                  ui_style_getFont( argUiText->stylePtr ),
                  argUiText->text,
                  ui_style_getColor( argUiText->stylePtr ) );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_text_blit(TUiText argUiText, SDL_Surface* argDestinationPtr)
{
    SDL_Rect lOffset    = ui_text_getRect( argUiText );


    /* On blitte la surface */
    SDL_BlitSurface( argUiText->sdl_surface,
                     NULL,
                     argDestinationPtr,
                     &lOffset );
}

/* ########################################################################## */
/* ########################################################################## */

TUiText ui_text_create(const char* argText, SStyle argStyle)
{
    TUiText retVal  = (TUiText)malloc( sizeof(struct _SUiTextPrivate) );


    retVal->alpha       = 0xFF;
    retVal->alignH      = EUiTextAlignLeft;
    retVal->alignV      = EUiTextAlignBottom;
    retVal->sdl_surface = 0;


    retVal->text        = strdup( argText );
    retVal->stylePtr    = argStyle;


    s_updateSurface( retVal );


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_text_delete(TUiText *argText)
{
    struct _SUiTextPrivate* p_struct    = (*argText);

    SDL_FreeSurface( p_struct->sdl_surface );
    FREE( p_struct->text );
    FREE( p_struct );

    (*argText)  = p_struct;
}

/* ########################################################################## */
/* ########################################################################## */

SDL_Rect    ui_text_getRect(TUiText argUiText)
{
    SDL_Rect    retVal;


    switch( argUiText->alignH )
    {
        case    EUiTextAlignLeft:
            retVal.x    = argUiText->posX;
            break;


        case    EUiTextAlignMiddle:
            retVal.x    = argUiText->posX - (argUiText->sdl_surface->w / 2);
            break;


        case    EUiTextAlignBottom:
        default:
            retVal.x    = argUiText->posX - argUiText->sdl_surface->w;
            break;
    }


    switch( argUiText->alignV )
    {
        case    EUiTextAlignTop:
            retVal.y    = argUiText->posY - argUiText->sdl_surface->h;
            break;


        case    EUiTextAlignMiddle:
            retVal.y    = argUiText->posY - (argUiText->sdl_surface->h / 2);
            break;


        case    EUiTextAlignBottom:
        default:
            retVal.y    = argUiText->posY;
            break;
    }


    retVal.h    = argUiText->sdl_surface->h;
    retVal.w    = argUiText->sdl_surface->w;


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_text_setAlign( TUiText               argUiText,
                          const TEUiTextAlignH  argAlignH,
                          const TEUiTextAlignV  argAlignV )
{
    argUiText->alignH   = argAlignH;
    argUiText->alignV   = argAlignV;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_text_setAlpha(TUiText argUiText, uint8_t argAlpha)
{
    argUiText->alpha    = argAlpha;

    SDL_SetAlpha( argUiText->sdl_surface,
                  SDL_SRCALPHA | SDL_RLEACCEL,
                  argUiText->alpha );
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_text_setPos(TUiText argUiText, Sint16 argPosX, Sint16 argPosY)
{
    argUiText->posX = argPosX;
    argUiText->posY = argPosY;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_text_setStyle(TUiText argUiText, SStyle argStyle)
{
    argUiText->stylePtr = argStyle;
    s_updateSurface( argUiText );
}

/* ########################################################################## */
/* ########################################################################## */
