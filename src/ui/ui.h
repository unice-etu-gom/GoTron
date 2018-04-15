#ifndef UI_H
#define UI_H

typedef struct _SUiContextPrivate*  TUiContext;


int ui_construct(TUiContext* argContextPtr);
int ui_destruct(TUiContext* argContextPtr);

int ui_exec(TUiContext* argContext);


void    ui_screenClear( TUiContext argContext );

#endif  /*< UI_H */
