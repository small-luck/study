#include "timerfd.h"
#include <iostream>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <sys/syscall.h>

unsigned long gettid()
{
    return (unsigned long)syscall(SYS_gettid); 
}


Timer::Timer()
{
    timer_map.clear();
    is_start = false;
    epoll_fd = -1;
}

Timer::~Timer() 
{
    if (is_start) {
        stop();
        is_start = false;
    }
}

int Timer::start()
{
    is_start = true;
    return create_epoll();
}

void Timer::stop()
{
    for (auto it = timer_map.begin(); it != timer_map.end(); it++) {
        close(it->first);
    }

    close(epoll_fd);
}

int Timer::add_timer(uint32_t interval, callback _cb, void * _arg)
{
    std::cout << "add_timer thread id = " << gettid() << std::endl;
    timer_event tevent;
    struct itimerspec timervalue;
    struct timespec now;
    struct epoll_event event;
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
    timervalue.it_interval.tv_nsec = 0;

    //create timerfd
    timerfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    if (timerfd == -1) {
        std::cout << "timerfd_create error: " << timerfd << std::endl;
        return timerfd;
    }

    //start timer
    ret = timerfd_settime(timerfd, 0, &timervalue, NULL);
    if (ret == -1) {
        std::cout << "timerfd_settime error: " << ret << std::endl;
        return ret;
    }

    tevent.timer_fd = timerfd;
    tevent.arg = _arg;
    tevent.cb = _cb;

    //use epoll_ctl
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = timerfd;
    
    ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timerfd, &event);
    if (ret != 0) {
        std::cout << "epoll_ctl error: " << ret << std::endl;
        return -1;
    }

    timer_map.insert(std::make_pair(timerfd, tevent));

    return timerfd;
}

int Timer::remove_timer(int timerfd)
{
    int ret;
    
    if (timerfd < 0) {
        std::cout << "arg is error" << std::endl;
        return -1;
    }

    auto it = timer_map.find(timerfd);
    if (it == timer_map.end()) {
        std::cout << "there is nosucktimerfd in timerfdMap" << std::endl;
        return 0;
    }

    ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, timerfd, 0);
    if (ret != 0) {
        std::cout << "epoll_ctl error: " << ret << std::endl;
        return -1;
    }

    timer_map.erase(it);
    close(timerfd);

    return 0;
}

int Timer::create_epoll()
{    
    epoll_fd = epoll_create(1);
    if (epoll_fd < 0) {
        std::cout << "epoll_create error: " << errno << std::endl;
        return -errno;
    }
    std::thread* thd = new std::thread(&Timer::timer_loop, this);
    thd->detach();
    
    return 0;
}

void Timer::timer_loop()
{
    std::cout << "timer_loop thread id = " << gettid() << std::endl;
    int n;
    int tmp = 10;
    int eventfd;
    uint64_t buf;
    struct epoll_event events[MAXEVENTS];
    callback func;

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
                    eventfd = events[i].data.fd;
                    read(eventfd, &buf, sizeof(uint64_t));
                    auto it = timer_map.find(eventfd);
                    if (it == timer_map.end()) {
                        std::cout << "eventfd: " << eventfd << " is not match in the map" << std::endl;
                        continue;
                    }
                    func = it->second.cb;
                    if (func) {
                        func(it->second.arg);
                    }
                }
            }
        }
    }
}
