#ifndef TCONTEXT_H
#define TCONTEXT_H

#include "core/grid.h"

typedef struct _SAudioContext*      TAudioContext;
typedef struct _SUiContextPrivate*  TUiContext;

/* ########################################################################## */
/* ########################################################################## */

typedef struct _SContext
{
    TAudioContext   audio;
    TUiContext      ui;
}   TContext;

/* ########################################################################## */
/* ########################################################################## */

#endif  /*< TCONTEXT_H */
