#ifndef UI_TTF_STYLES_H
#define UI_TTF_STYLES_H

#include <SDL_ttf.h>


typedef struct _SUiTTFStylePrivate* SStyle;


extern const char*  C_FONT_TRON;

extern SDL_Color    C_SDL_COLOR_BLACK;
extern SDL_Color    C_SDL_COLOR_GREY50;
extern SDL_Color    C_SDL_COLOR_WHITE;
extern SDL_Color    C_SDL_COLOR_RED;
extern SDL_Color    C_SDL_COLOR_YELLOW;
extern SDL_Color    C_SDL_COLOR_GREEN;
extern SDL_Color    C_SDL_COLOR_AQUA;
extern SDL_Color    C_SDL_COLOR_AQUA50;
extern SDL_Color    C_SDL_COLOR_BLUE;
extern SDL_Color    C_SDL_COLOR_PINK;


int     ui_style_create( SStyle*            argStylePtr,
                         const char*        argFontFilePath,
                         const size_t       argSize,
                         const SDL_Color    argColor );
void    ui_style_delete( SStyle*            argStylePtr );


TTF_Font*   ui_style_getFont( const SStyle argStyle );
SDL_Color   ui_style_getColor( const SStyle argStyle );


#endif
