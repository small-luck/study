#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/syscall.h>

int count = 0;

unsigned long gettid()
{
    return (unsigned long)syscall(SYS_gettid);
}

void print()
{     
    while (count < 3000) {
        ++count;
        std::cout << "thread_id = " << gettid() << "; count= " << count << std::endl;
    }
}

int main(int argc, char const * argv [ ])
{
    std::thread *threads[5];

    for (int i = 0; i < 5; i++) {
        threads[i] = new std::thread(&print);
    } 


    //for (int i = 0; i < 5; i++) {
    //    threads[i]->join();
    //}
    while(1) {

    }
    return 0;
}