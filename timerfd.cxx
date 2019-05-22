//实现timerfd定时器
#include <iostream>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <time.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    int ret;
    int epoll_fd;
    int timer_fd;

    struct itimerspec new_value;
    struct timespec now;

    //获取时钟时间
    ret = clock_gettime(CLOCK_REALTIME, &now);
    if (ret == -1) {
        std::cout << "clock_gettime fail" << std::endl;
        exit(-1);
    }

    //设置第一次到期时间
    new_value.it_value.tv_sec = 5;
    new_value.it_value.tv_nsec = 0;

    //设置之后每次到期的时间间隔
    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_nsec = 0;

    //构建一个定时器
    timerfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    if (timerfd == -1) {
        std::cout << "timerfd_create fail" << std::endl;
        exit(-1);
    }

    //启动定时器
    ret = timerfd_settime(timerfd, 0, &new_value, NULL);
    if (ret == -1) {
        std::cout << "timerfd_settime fail" << std::endl;
        exit(-1);
    }

    std::cout << "timer start" << std::endl;

    //创建epoll fd
    
    return 0;
}