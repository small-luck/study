#ifndef _UTILS_H_
#define _UTILS_H_


#include <pthread.h>
#include <iostream>

#define ABS(key) ((key) >= 0 ? (key) : -(key))



void mutex_lock_init(pthread_mutex_t *mutex);
void mutex_lock_destory(pthread_mutex_t *mutex);
int  do_mutex_lock(pthread_mutex_t *mutex);
int  do_mutex_unlock(pthread_mutex_t *mutex);
uint64_t get_current_msec(void);



#endif /*_UTILS_H_*/