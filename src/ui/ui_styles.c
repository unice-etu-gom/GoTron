#include "ui_styles.h"

/* ########################################################################## */
/* ########################################################################## */

#include "core/log/log.h"

#define TRACE_DBG(format,...) \
        TRACE_DBG_BASE( "ui_ttf_style", format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...) \
        TRACE_ERR_BASE( "ui_ttf_style", format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

struct  _SUiTTFStylePrivate
{
    TTF_Font*   p_font;
    SDL_Color   color;
    size_t      size;
};

/* ########################################################################## */
/* ########################################################################## */

SDL_Color   C_SDL_COLOR_BLACK   = {   0,      0,      0 };
SDL_Color   C_SDL_COLOR_GREY50  = { 128,    128,    128 };
SDL_Color   C_SDL_COLOR_WHITE   = { 255,    255,    255 };
SDL_Color   C_SDL_COLOR_RED     = { 255,      0,      0 };
SDL_Color   C_SDL_COLOR_YELLOW  = { 255,    255,      0 };
SDL_Color   C_SDL_COLOR_GREEN   = {   0,    255,      0 };
SDL_Color   C_SDL_COLOR_AQUA    = {   0,    255,    255 };
SDL_Color   C_SDL_COLOR_AQUA50  = {   0,    128,    128 };
SDL_Color   C_SDL_COLOR_BLUE    = {   0,      0,    255 };
SDL_Color   C_SDL_COLOR_PINK    = { 255,      0,    255 };


const char* C_FONT_TRON        = "Tr2n.ttf";
//const char* C_FONT_TITLE        = "TRON.TTF";

/* ########################################################################## */
/* ########################################################################## */

int     ui_style_create( SStyle*            argStylePtr,
                         const char*        argFontFilePath,
                         const size_t       argSize,
                         const SDL_Color    argColor )
{
    int retVal  = EXIT_SUCCESS;


    (*argStylePtr)  = (SStyle)malloc( sizeof( struct _SUiTTFStylePrivate ) );


    if(     ((*argStylePtr)->p_font  = TTF_OpenFont( argFontFilePath, argSize ))
        ==  NULL )
    {
        retVal  = EXIT_FAILURE;
        TRACE_ERR( "Font init error : %s",
                   TTF_GetError() );
    }
    else
    {
        (*argStylePtr)->size    = argSize;
        (*argStylePtr)->color   = argColor;
    }


    return EXIT_SUCCESS;
}

/* ########################################################################## */
/* ########################################################################## */

void    ui_style_delete(SStyle *argStylePtr)
{
    TTF_CloseFont( (*argStylePtr)->p_font );
}

/* ########################################################################## */
/* ########################################################################## */

SDL_Color   ui_style_getColor(const SStyle argStyle)
{
    return argStyle->color;
}

/* ########################################################################## */
/* ########################################################################## */

TTF_Font*   ui_style_getFont(SStyle argStyle)
{
    return  argStyle->p_font;
}

/* ########################################################################## */
/* ########################################################################## */
