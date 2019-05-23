/*实现一个经典的epoll服务程序*/
#include <sys/epoll.h>
#include <fcntl.h>
#include <thread>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define set_nonblock(fd) \
    do { \
        int flags = fcntl(fd, F_GETFL, 0); \
        flags |= O_NONBLOCK; \
        fcntl(fd, F_SETFL, flags); \
    } while(0)

#define LISTENMAX 10
#define EVENTNUM  64
#define BUFFSIZE 4096 

int create_socket(int port, char* ip, struct sockaddr_in* addrinfo)
{
    int sockfd;
    int on = 1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cout << "socket fail" << std::endl;
        return -1;
    }

    set_nonblock(sockfd);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    addrinfo->sin_family = AF_INET;
    addrinfo->sin_port = htons(port);
    addrinfo->sin_addr.s_addr = inet_addr(ip);

    return sockfd;
}

int main(int argc, char const *argv[])
{
    int socket_fd;
    int epoll_fd;
    int client_fd;
    int ret;
    int count;
    int port;
    int n;
    socklen_t addrlen;
    char* ipaddr;
    char buffer[BUFFSIZE];
    struct sockaddr_in seraddr, clientaddr;
    struct epoll_event event, events[EVENTNUM];

    if (argc != 3) {
        std::cout << "argc num error" << std::endl;
        exit(-1);
    }

    port = atoi((char*)argv[1]);
    ipaddr = (char*)argv[2];

    std::cout << "port = " << port << std::endl;
    std::cout << "ipaddr = " << ipaddr << std::endl;

    memset(&seraddr, 0, sizeof(seraddr));
    socket_fd = create_socket(port, ipaddr, &seraddr);
    if (socket_fd < 0) {
        std::cout << "create_socket fail" << std::endl;
        exit(-1);
    }

    //bind
    ret = bind(socket_fd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    if (ret != 0) {
        std::cout << "bind error" << std::endl;
        exit(-1);
    }

    //listen
    ret = listen(socket_fd, LISTENMAX);
    if (ret != 0) {
        std::cout << "listen error" << std::endl;
        exit(-1);
    }

    //create epoll fd
    epoll_fd = epoll_create(1);
    if (epoll_fd < 0) {
        std::cout << "epoll_create fail" << std::endl;
        exit(-1);
    }

    event.events = EPOLLIN | EPOLLET;
    event.data.fd = socket_fd;

    //epoll ctl
    ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event);
    if (ret != 0) {
        std::cout << "epoll_ctl error" << std::endl;
        exit(-1);
    }

    while (true) {
        count = epoll_wait(epoll_fd, events, EVENTNUM, 0);
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                memset(buffer, 0, BUFFSIZE);
                 memset(&event, 0, sizeof(event));
                if (events[i].data.fd == socket_fd) {   //有新的连接到来
                    memset(&clientaddr, 0, sizeof(clientaddr));
                    client_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, &addrlen);
                    if (client_fd < 0) {
                        std::cout << "accept error" <<std::endl;
                        continue;
                    }
                    std::cout << "client " << client_fd << " is connecting!!!" << std::endl;
                    set_nonblock(client_fd);
                    event.events = EPOLLIN | EPOLLET;
                    event.data.fd = client_fd;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
                } else if (events[i].events & EPOLLIN) {
                    n = read(events[i].data.fd, buffer, BUFFSIZE);
                    if (n > 0) {
                        std::cout << "recieve msg: " << buffer << std::endl;
                    }
                    event.data.fd = events[i].data.fd;
                    event.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, events[i].data.fd, &event);
                } else if (events[i].events & EPOLLOUT) {
                    strcpy(buffer, "i am server point!");
                    n = write(events[i].data.fd, buffer, strlen(buffer));
                    event.data.fd = events[i].data.fd;
                    event.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, events[i].data.fd, &event);
                }
            }
        }
    }
    return 0;
}