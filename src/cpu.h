#ifndef CPU_H
#define CPU_H

#include <functional>
#include <unordered_map>
#include "registers.h"
#include "memory.h"
#include "byte.h"

namespace gameboy {
    class cpu {
    public:
        cpu(memory& mem);
        void fetch();
    private:
        static constexpr auto CYCLES_PER_FRAME = 70244;
        registers _registers;
        memory& _memory;
        int _cycle;
        std::unordered_map<byte, std::function<void()>> _instruction_map;
    };
}

#endif