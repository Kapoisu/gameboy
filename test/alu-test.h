#ifndef ALU_TEST_H
#define ALU_TEST_H

#include "alu.h"

namespace gameboy {
    class alu_test {
    public:
        template<typename T>
        bool test_addition() const;
        template<typename T>
        bool test_subtraction() const;

        bool test_daa() const;
    private:
        gameboy::alu _alu;
    };
}

#endif