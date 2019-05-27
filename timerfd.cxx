//实现timerfd定时器
#include <iostream>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define EPOLLNUM 64

void time_func(void)
{
    std::cout << "it is time to do something..." << std::endl;
}

int main(int argc, char const *argv[])
{
    int ret;
    int epoll_fd;
    int timerfd;
    uint64_t exp;

    struct itimerspec new_value;
    struct timespec now;
    struct epoll_event event, events[EPOLLNUM];

    //获取时钟时间
    ret = clock_gettime(CLOCK_REALTIME, &now);
    if (ret == -1) {
        std::cout << "clock_gettime fail" << std::endl;
        exit(-1);
    }

    //设置第一次到期时间
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_nsec = 0;

    //设置之后每次到期的时间间隔
    new_value.it_interval.tv_sec = 3;
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
    epoll_fd = epoll_create(1);
    if (epoll_fd < 0) {
        std::cout << "epoll_create fail" << std::endl;
        exit(-1);
    }

    event.events = EPOLLIN | EPOLLET;
    event.data.fd = timerfd;

    ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timerfd, &event);
    if (ret != 0) {
        std::cout << "epoll_ctl error" << std::endl;
        exit(-1);
    }

    while (true) {
        int n = epoll_wait(epoll_fd, events, EPOLLNUM, 1000);
        std::cout << "n = " << n << std::endl;
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (events[i].events & EPOLLIN) {
                    if (events[i].data.fd == timerfd) {
                        read(events[i].data.fd, &exp, sizeof(uint64_t));
                        time_func();
                    }
                }
            }
        }
    }
    return 0;
}
