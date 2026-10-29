#include "POUS.h"
#include "Config0.h"

void MAIN_init__(MAIN *data__, BOOL retain) {
  __INIT_VAR(data__->COUNTER,0,retain)
  __INIT_LOCATED(BOOL,__IX1_0,data__->BUTTON,retain)
  __INIT_LOCATED_VALUE(data__->BUTTON,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX1_0,data__->LIGHT,retain)
  __INIT_LOCATED_VALUE(data__->LIGHT,__BOOL_LITERAL(FALSE))
}

// Code part
void MAIN_body__(MAIN *data__) {
  // Initialise TEMP variables

  if (__GET_LOCATED(data__->BUTTON,)) {
    __SET_LOCATED(data__->,LIGHT,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,COUNTER,,1);
  } else {
    __SET_LOCATED(data__->,LIGHT,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,COUNTER,,0);
  };

  goto __end;

__end:
  return;
} // MAIN_body__() 





