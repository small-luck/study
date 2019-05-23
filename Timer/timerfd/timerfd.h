#ifndef _TIMEFD_H_
#define _TIMEFD_H_
/*
利用linux自带的timefd和epoll，封装一个秒级的定时器
*/

#include <iostream>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <map>

#define MAXEVENTS 10
#define EPOLLWAITTIME 1000

typedef void (*callback)(void);

struct timer_event {
    int timer_fd;
    callback cb;
    void* arg;
};

class Timer {
    public:    
        Timer();
        virtual ~Timer();

        int start();
        int stop();
        
        int add_timer(uint32_t interval, callback _cb, void * _arg);
        int remove_timer();

        int create_epoll();
        void* timer_loop();

    private:
         int epoll_fd;
         std::map<int, timer_event> timer_map;
         bool is_start;
};


#endif
