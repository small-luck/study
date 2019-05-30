#ifndef _NET_H_
#define _NET_H_

#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>


#define PORT        8323
#define IP          "127.0.0.1"

#define LISTEN_MAX  10

#define set_nonblock(fd)                \
    int old = fcntl(fd, F_GETFL, 0);    \
    old |= O_NONBLOCK;                  \
    fcntl(fd, F_SETFL, old);

#define set_resueaddr(fd)               \
    int on = 1;                         \
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));  
    

class Socket {
    public:
        Socket() {
            listen_fd = -1;
            memset(&seraddr, 0, sizeof(seraddr));
        }
        virtual ~Socket() {}

        int get_listen_fd() {
            return listen_fd;
        }
        struct sockaddr_in get_seraddr() {
            return seraddr;
        }

        int init_socket();
        int Bind();
        int Listen();
        int Accept(struct sockaddr_in *cliaddr, socklen_t addrlen);
        
    private:
        int listen_fd;
        struct sockaddr_in seraddr;
};

class Epoll {
    public:
        Epoll() {
            epoll_fd = -1;
        }

        virtual ~Epoll() {}

        int Epoll_create();
        int Epoll_ctl(int op, int fd, struct epoll_event *ev);
        int Epoll_wait(struct epoll_event *events, int maxevents, int timeout);
        
    private:
        int epoll_fd;
        
};

#endif /*_NET_H_*/

