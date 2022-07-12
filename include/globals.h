#ifndef __GLOBALS_H_INCLUDE__
#define __GLOBALS_H_INCLUDE__

#include <stdint.h>

#define MAX_TEXT_BUFFER_SIZE 256

#ifndef DEBUG_ENABLED
    #define DEBUG_ENABLED 1 
#endif

extern uint8_t text_buffer[MAX_TEXT_BUFFER_SIZE];   // temporary buffer for rendering of text

#define STATES \
_STATE(state_logo)\
_STATE(state_gallery)\
_STATE(state_thumbnails)\
STATE_DEF_END

#define DEFAULT_STATE state_logo 

#endif