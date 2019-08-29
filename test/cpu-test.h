#ifndef CPU_TEST_H
#define CPU_TEST_H

#include "cpu.h"
#include "memory.h"

namespace gameboy {
    class cpu_test {
    public:
        cpu_test(memory& mem);
    private:
        cpu _cpu;
    };
}

#endif