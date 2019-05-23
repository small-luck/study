#include "timerfd.h"

Timer::Timer()
{
    timer_map.clear();
    is_start = false;
    epoll_fd = -1;
}

Timer::~Timer() 
{

}

int Timer::start()
{
    return create_epoll();
}

int Timer::stop()
{

}

int Timer::add_timer(uint32_t interval, callback _cb, void * _arg)
{
    timer_event tevent;
    struct itimespec timervalue;
    struct timespec now;
    int timerfd;
    int ret;
    
    //get current time
    ret = clock_gettime(CLOCK_REALTIME, &now);
    if (ret == -1) {
        std::cout << "clock_gettime error: " << ret << std::endl;
        return ret;
    }

    //set first expire time
    timervalue.it_value.tv_sec = interval;
    timervalue.it_value.tv_nsec = 0;

    //set expire time after the first expireation
    timervalue.it_interval.tv_sec = interval;
    timervalue.it_interval.tv_nsrc = 0;

    //create timerfd
    timerfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    if (timerfd == -1) {
        std::cout << "timerfd_create error: " << timerfd << std::endl;
        return timerfd;
    }

    tevent.timer_fd = timerfd;
    tevent.arg = _arg;
    tevent.cb = _cb;

    timer_map.insert(std::make_pair(timerfd, tevent));

    //use epoll_ctl
}

int Timer::remove_timer()
{

}

int Timer::create_epoll()
{
    int ret;
    struct epoll_event event;
    
    epoll_fd = epoll_create(1);
    if (epoll_fd < 0) {
        std::cout << "epoll_create error: " << errno << std::endl;
        return -errno;
    }

    std::thread thd(timer_loop);
    thd.detch();
    
}

void* Timer::timer_loop()
{
    int n;
    int ret;
    struct epoll_event events[MAXEVENTS];

    while (true) {
        n = epoll_wait(epoll_fd, events, MAXEVENTS, EPOLLWAITTIME);
        if (n < 0) {
            std::cout << "epoll_wait error" << std::endl;
            continue;
        } else if (n == 0) {
            std::cout << "epoll_wait time out" << std::endl;
            continue;
        } else {
            for (int i = 0; i < n; i++) {
                if (events[i].events & EPOLLIN) {
                    //判断events[i].data.fd是否在timer_map中
                    //调用对应的回调函数
                }
            }
        }
    }
}
