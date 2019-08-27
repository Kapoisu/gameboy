#include "registers.h"

namespace gameboy {
    registers::registers()
        : accumulator(0)
        , general_b(_general_bc.bytes.high)
        , general_c(_general_bc.bytes.low)
        , general_bc(_general_bc.value)
        , general_d(_general_de.bytes.high)
        , general_e(_general_de.bytes.low)
        , general_de(_general_de.value)
        , general_h(_general_hl.bytes.high)
        , general_l(_general_hl.bytes.low)
        , general_hl(_general_hl.value)
        , stack_pointer(0)
        , program_counter(0)
    {
    }
}