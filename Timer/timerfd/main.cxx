#include "timerfd.h"
#include <iostream>


void func1(void* arg)
{
    int n = *(int*)arg;
    std::cout << "n = " << n << std::endl;
}

void func2(void* arg)
{
    int s = *(int*)arg;
    std::cout << "s = " << s<< std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << "main thread id = " << gettid() << std::endl;
    int number = 10;
    int stmp = 20;
    int timer_fd;
    Timer timer;
    
    timer.start();
    timer_fd = timer.add_timer(3, func1, (void*)&number);
    timer_fd = timer.add_timer(5, func2, (void*)&stmp);
        
    while(1) {

    }
    return 0;
}