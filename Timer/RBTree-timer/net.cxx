#include "net.h"

#include <iostream>
#include <sys/epoll.h>
#include <arpa/inet.h>

int Socket::init_socket()
{
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        return listen_fd;
    }

    set_nonblock(listen_fd);
    
    set_resueaddr(listen_fd);

    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(PORT);
    seraddr.sin_addr.s_addr = inet_addr(IP);

    return 0;   
}

int Socket::Bind()
{
    return (bind(listen_fd, (struct sockaddr*)&seraddr, sizeof(seraddr)));
}

int Socket::Listen()
{
    return (listen(listen_fd, LISTEN_MAX));
}

int Socket::Accept(struct sockaddr_in * cliaddr, socklen_t addrlen)
{
    return (accept(listen_fd, (struct sockaddr*)cliaddr, &addrlen));    
}

int Epoll::Epoll_create()
{
    epoll_fd = epoll_create(1);
    if (epoll_fd < 0) {
        return epoll_fd;
    }

    return 0;
}

int Epoll::Epoll_ctl(int op, int fd, struct epoll_event *ev)
{
    return (epoll_ctl(epoll_fd, op, fd, ev));
}

int Epoll::Epoll_wait(struct epoll_event *events, int maxevents, int timeout)
{
    return (epoll_wait(epoll_fd, events, maxevents, timeout));
}

