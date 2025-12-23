#ifndef BOARD_H
#define BOARD_H

#if defined(FW_BOARD_NANO)
    #include "nano.h"
#elif defined(FW_BOARD_UNO)
    #include "uno.h"
#else // No board defined
    #warning "No board defined. Defaulting to UNO."
    #include "uno.h" // Default
#endif

#endif // BOARD_H