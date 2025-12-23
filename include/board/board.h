#ifndef BOARD_H
#define BOARD_H

#include "board_def.h"

#if defined(FW_BOARD_NANO)
    #include "nano.h"
#elif defined(FW_BOARD_UNO)
    #include "uno.h"
#else
    #error "No board defined"
#endif

#endif // BOARD_H