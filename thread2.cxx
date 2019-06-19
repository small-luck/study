#include <iostream>
#include <thread>

class Print {
    public:
        void print(int num) {
            std::cout << "num = " << num << std::endl;
        }
};

int main(int argc, char *argv[])
{
    Print *p = new Print();
    std::thread *th = new std::thread(std::bind(&Print::print, p, 300));
    th->join();
    
    return 0;
}
