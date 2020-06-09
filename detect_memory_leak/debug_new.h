#ifndef DEBUG_NEW_H
#define DEBUG_NEW_H

//#ifndef NDEBUG

#include "track_new.h"
#define new new(__FILE__,__LINE__)

//#endif // !NDEBUG


#endif DEBUG_NEW_H //!DEBUG_NEW_H
