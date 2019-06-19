/*
    C++11多线程编程
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <sys/syscall.h>
#include <unistd.h>

unsigned long gettid()
{
    return (unsigned long)syscall(SYS_gettid);
}

void print(int num)
{
    std::cout << "child thread_id = " << gettid() << std::endl;
    std::cout << "num = " << num << std::endl;
}


int main(int argc, char *argv[])
{
    std::cout << "main thread_id = " << gettid() << std::endl;
    int n = 100;
    
    std::thread th(&print, n);
    th.join();
    
    return 0;
}
