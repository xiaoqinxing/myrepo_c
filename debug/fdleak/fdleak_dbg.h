#ifndef __FDLEAK_H__
#define __FDLEAK_H__

#include <pthread.h>

#define DUMP_FDLEAK_TRACE 1
#define FDLEAK_EXIT 2

extern pthread_mutex_t fdleak_mut;
extern pthread_cond_t fdleak_con;
extern char fdleak_event;
#ifdef __cplusplus
extern "C" {
#endif
void * fdleak_thread (void * param __unused);
void enable_fdleak_trace();
void dump_fdleak_trace();
#ifdef __cplusplus
}
#endif

#endif
