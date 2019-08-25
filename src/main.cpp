#include <thread>
#include <chrono>
#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "registers.h"

int main()
{
    using namespace gameboy;
    using namespace std::chrono_literals;

    std::thread worker([]()
    {
        memory mem;
        cpu processor(mem);
        while(true) {
            //std::cout << "fetch" << std::endl;
            processor.fetch();
            std::this_thread::sleep_for(1s);
        }
    });

    worker.detach();

    std::cin.get();

    return 0;
}