#ifndef _UTILS_H_
#define _UTILS_H_

#define abs(key) ((key) >= 0 ? (key) : -(key))



void mutex_init(pthread_mutex_t *mutex);
void mutex_destory(pthread_mutex_t *mutex);
void mutex_lock(pthread_mutex_t *mutex);
void mutex_unlock(pthread_mutex_t *mutex);
uint64_t get_current_msec(void);



#endif /*_UTILS_H_*/