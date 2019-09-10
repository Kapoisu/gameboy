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

        template<typename T, typename U>
        output<T> add(T operand1, U operand2, bool carry = false) const
        {
            constexpr auto half_mask = (1 << (sizeof(T) * 8 / 2)) - 1;
            constexpr auto full_mask = (1 << (sizeof(T) * 8)) - 1;
            integer_result<T> result{operand1 + operand2};
            output<T> output{result.value};
            output.status[flag_type::zero] = result.value == 0;
            output.status[flag_type::subtract] = false;
            output.status[flag_type::half_carry] = (operand1 & half_mask) + (operand2 & half_mask) + carry > half_mask;
            output.status[flag_type::carry] = (operand1 & full_mask) + (operand2 & full_mask) + carry > full_mask;

            return output;
        }

        template<typename T, typename U>
        output<T> subtract(T operand1, U operand2, bool carry = false) const
        {
            constexpr auto half_mask = (1 << (sizeof(T) * 8 / 2)) - 1;
            constexpr auto full_mask = (1 << (sizeof(T) * 8)) - 1;
            integer_result<T> result{operand1 - operand2};
            output<T> output{result.value};
            output.status[flag_type::zero] = result.value == 0;
            output.status[flag_type::subtract] = true;
            output.status[flag_type::half_carry] = (operand1 & half_mask) - (operand2 & half_mask) - carry < 0;
            output.status[flag_type::carry] = (operand1 & full_mask) - (operand2 & full_mask) - carry < 0;

            return output;
        }

        output<byte> and_byte(byte operand1, byte operand2) const;
        output<byte> xor_byte(byte operand1, byte operand2) const;
        output<byte> or_byte(byte operand1, byte operand2) const;

        output<byte> daa(byte number, const flags& flag) const;
    };
}

#endif