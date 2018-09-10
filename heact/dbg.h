#ifndef __HEACT_DBG_H__
#define __HEACT_DBG_H__ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define HEACT_DEBUG_NONE 0
#define HEACT_DEBUG_VERBOSE 1
#define HEACT_DEBUG_NOTICE 2
#define HEACT_DEBUG_WARNING 4
#define HEACT_DEBUG_ERROR 8

#define HEACT_DEBUG_ALL 0xffU

int heact_debug_level_get();
int heact_debug_level_set(int val);

#if defined(DEBUG) || defined(_DEBUG)
	#ifdef __GNUC__
		#define debug_printf(i,a,...) {if((heact_debug_level_get() & i) == i)printf(__FILE__  "/%s/%d:" a "\r\n",__FUNCTION__,__LINE__,__VA_ARGS__);}
	#else
		#define debug_printf(i,a,...) {if((heact_debug_level_get() & i) == i)printf(__FILE__  "/"  __FUNCTION__  "/%d:" a "\r\n",__LINE__,__VA_ARGS__);}
	#endif
#else
inline static void dummy_printf() {}
#define debug_printf(...) dummy_printf()
#endif

#ifdef __cplusplus
}
#endif

#endif
