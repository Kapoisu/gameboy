#ifndef REGISTERS_H
#define REGISTERS_H

#include "byte.h"
#include "word.h"

namespace gameboy {
    int make_address(byte high, byte low);

    struct registers {
    public:
        registers();
        byte accumulator; // used for small value calculation
        byte flag;
        byte& general_b;
        byte& general_c;
        unsigned short& general_bc;
        byte& general_d;
        byte& general_e;
        unsigned short& general_de;
        byte& general_h;
        byte& general_l;
        unsigned short& general_hl;
        unsigned short stack_pointer;
        unsigned short program_counter;
    private:
        word _general_bc;
        word _general_de;
        word _general_hl;
    };
}

#endif