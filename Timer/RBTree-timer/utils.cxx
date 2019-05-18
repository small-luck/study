#include "utils.h"
#include <iostream>

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