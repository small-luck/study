#include <iostream>
#include "net.h"

int main(int argc, char* argv[])
{
    int ret;
    int listenfd;
    int clientfd;
    Socket sock;
    struct sockaddr_in clientaddr;
    socklen_t addrlen;

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

    while (1) {
        memset(&clientaddr, 0, sizeof(clientaddr));
        
        clientfd = sock.Accept(&clientaddr, addrlen);
        if (clientfd < 0) {
            continue;
        }

        std::cout << "connect success! clientfd = " << clientfd << std::endl;
    }
    

    return 0;
}