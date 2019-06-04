#include "utils.h"
#include <iostream>
#include <sys/time.h>

void mutex_lock_init(pthread_mutex_t * mutex)
{
    if (mutex != NULL) {
        return;
    }

    pthread_mutex_init(mutex, NULL);

}

void mutex_lock_destory(pthread_mutex_t *  mutex)
{
    pthread_mutex_destroy(mutex);
}

int do_mutex_lock(pthread_mutex_t *mutex)
{
    int ret;
    
    ret = pthread_mutex_lock(mutex);
    if (ret != 0) {
        std::cout << "pthread_mutex_lock error: " << ret << std::endl;
        return -1;
    }
    
    return 0;
}

int do_mutex_unlock(pthread_mutex_t *mutex)
{
    int ret;

    ret = pthread_mutex_unlock(mutex);
    if (ret != 0) {
        std::cout << "pthread_mutex_unlock ewrror: " << ret << std::endl;
        return -1;
    }

    return 0;
}

uint64_t get_current_msec(void)
{
    struct timeval now;
    uint64_t sec;
    uint64_t msec;
    uint64_t now_msec;

    gettimeofday(&now, NULL);

    sec = now.tv_sec;
    msec = now.tv_usec / 1000;

    now_msec = sec * 1000 + msec;

    return now_msec;
}