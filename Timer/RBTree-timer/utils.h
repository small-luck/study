#ifndef _UTILS_H_
#define _UTILS_H_

#include <pthread.h>

void mutex_init(pthread_mutex_t *mutex);
void mutex_destory(pthread_mutex_t *mutex);
void mutex_lock(pthread_mutex_t *mutex);
void mutex_unlock(pthread_mutex_t *mutex);



#endif /*_UTILS_H_*/