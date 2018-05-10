#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <SDL_events.h>


void    input_init(void);

SDLKey  input_keyboardEvent_poll(void);

void    input_printKeyInfo( SDL_KeyboardEvent *key );
void    input_printModifiers( SDLMod mod );



#if 0
#include <SDL_thread.h>


typedef struct SKeyboardInput*  TKeyboardInput;


TKeyboardInput  keyboardInput_create(void);
void            keyboardInput_destroy( TKeyboardInput* argEltToDestroy);

void            keyboardInput_start( TKeyboardInput argElt );
void            keyboardInput_stop( TKeyboardInput argElt );
#endif


#endif  /*< INPUT_H */
