#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <stddef.h>

#include "core/TBool.h"

/* ########################################################################## */
/* ########################################################################## */

typedef struct  _SHighScore
{
    char*   pseudo;
    int     score;
}   THighScore;


typedef struct _SHighscoresListElt* THighscoresListElt;

struct _SHighscoresListElt
{
    THighScore          data;
    THighscoresListElt  next;
};


THighscoresListElt  highscoreElt_create( const char* argPseudo, int argScore );
void                highscoreElt_destroy( THighscoresListElt* argElt );

/* ########################################################################## */
/* ########################################################################## */

typedef THighscoresListElt THighscoresList;

extern const size_t C_HIGHSCORES_MAXCOUNT;


THighscoresList highscoresList_load(void);
void            highscoresList_save(THighscoresList argList);

void    highscoresList_insertEltOrdered(THighscoresList*       argListPtr,
                                         THighscoresListElt argEltPtr );

void    highscoresList_print(THighscoresList argList);


TBool   highscoresList_checkIfAccepted(THighscoresList argList, int argScore);

/* ########################################################################## */
/* ########################################################################## */

#endif  /*< HIGHSCORES_H */
