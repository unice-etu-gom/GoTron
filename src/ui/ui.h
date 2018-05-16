#ifndef UI_H
#define UI_H

#include "core/TContext.h"


int ui_construct(TContext* argContextPtr);
int ui_destruct(TContext* argContextPtr);

int ui_exec(TContext* argContext);

#endif  /*< UI_H */
