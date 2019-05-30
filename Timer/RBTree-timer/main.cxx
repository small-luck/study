#include <iostream>
#include "net.h"
#include "timer.h"

#define MAX_EVENT   64
#define TIMEOUT     10 * 1000


void print(event_t ev)
{
    int fd = ev->fd;

    std::cout << "client fd: " << fd << " is timeout" << std::endl;
}

int main(int argc, char* argv[])
{
    int ret;
    int listenfd;
    int clientfd;
    int n;
    int timer;
    Socket sock;
    Epoll epoll;
    struct sockaddr_in clientaddr;

    struct epoll_event event, events[MAX_EVENT];

    ret = sock.init_socket();
    if (ret != 0) {
        std::cout << "init_socket error, ret = " << ret << std::endl;
        return -1;
    }

    ret = sock.Bind();
    if (ret != 0) {
        std::cout << "Bind error, ret = " << ret << std::endl;
        return -1;
    }

    ret = sock.Listen();
    if (ret != 0) {
        std::cout << "Listen error, ret = " << ret << std::endl;
        return -1;
    }

    listenfd = sock.get_listen_fd();
    std::cout << "listenfd = " << listenfd << std::endl;

    ret = epoll.Epoll_create();
    if (ret != 0) {
        std::cout << "Epoll_create error, ret = " << ret << std::endl;
    }

    event.data.fd = listenfd;
    event.events  = EPOLLIN | EPOLLET;
    ret = epoll.Epoll_ctl(EPOLL_CTL_ADD, listenfd, &event);
    if (ret != 0) {
        std::cout << "Epoll_ctl error, ret = " << ret << std::endl;
    }

    //register callback for fd,set a timer
    event_t ev;
    event_timer_init();
    ev.fd = listenfd;
    ev.handler = print;
    event_add_timer(&ev, TIMEOUT);

    while (1) {
        timer = event_find_timer();
        std::cout << "Epoll_wait timer = " << timer << std::endl;
        n = epoll.Epoll_wait(events, MAX_EVENT, timer);
        if (n == 0) {
            std::cout << "Epoll_wait timeout!!!" << std::endl;
        } else if (n < 0) {
            std::cout << "Epoll_wait error, ret = " << n << std::endl;
        } else {
            for (int i = 0; i < n; i++) {
                if (events[i].data.fd == listenfd) {
                    memset(&clientaddr, 0, sizeof(clientaddr));
        
                    clientfd = sock.Accept(&clientaddr);
                    if (clientfd < 0) {
                        continue;
                    }

                    std::cout << "connect success! clientfd = " << clientfd << std::endl;
                } else {
                    //TODO
                }
            }
        }

        //处理超时事件
        std::cout << "start handler timeout events" << std::endl;
        event_expire_timers();
    }    

    return 0;
}
