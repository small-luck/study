#include "utils.h"
#include <iostream>
#include <sys/time.h>
#include <pthread.h>

void mutex_init(pthread_mutex_t * mutex)
{
    if (mutex != NULL) {
        return;
    }

    mutex = mew pthread_mutex_t();

    pthread_mutex_init(mutex, NULL);

}

void mutex_destory(pthread_mutex_t * mutex)
{
    if (mutex == NULL)
        return;

    pthread_mutex_destory(mutex);

    delete mutex;
    mutex = NULL;
}

int mutex_lock(pthread_mutex_t *mutex)
{
    int ret;

    ret = pthread_mutex_lock(mutex);
    if (ret != 0) {
        std::cout << "pthread_mutex_lock error: " << ret << std::endl;
        return -1;
    }

    return 0;
}

int mutex_unlock(pthread_mutex_t *mutex)
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