#ifndef TCONTEXT_H
#define TCONTEXT_H

#include "core/grid.h"

typedef struct _SUiContextPrivate*  TUiContext;

/* ########################################################################## */
/* ########################################################################## */

typedef struct _SContext
{
    TCoreGrid   grid;
    TUiContext  ui;
}   TContext;

/* ########################################################################## */
/* ########################################################################## */

#endif  /*< TCONTEXT_H */
