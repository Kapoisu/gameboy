#ifndef ALU_H
#define ALU_H

#include "flags.h"

namespace gameboy {
    class alu {
    private:
        template<typename T>
        union integer_result {
        public:
            explicit integer_result(int value) : value_with_promotion(value)
            {
            }
            T value;
        private:
            int value_with_promotion;
        };
    public:
        template<typename T>
        struct output {
            T result;
            flags status;
        };

        template<typename T>
        output<T> add(T operand1, T operand2, bool carry = false) const;

        template<typename T>
        output<T> subtract(T operand1, T operand2, bool carry = false) const;

        output<byte> and_byte(byte operand1, byte operand2) const;
        output<byte> xor_byte(byte operand1, byte operand2) const;
        output<byte> or_byte(byte operand1, byte operand2) const;

        output<byte> daa(byte number, const flags& flag) const;
    };
}

#endif