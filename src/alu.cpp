#include "alu.h"

namespace gameboy {
    template<typename T>
    alu::output<T> alu::add(T operand1, T operand2, bool carry) const
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

    template<typename T>
    alu::output<T> alu::subtract(T operand1, T operand2, bool carry) const
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

    alu::output<byte> alu::and_byte(byte operand1, byte operand2) const
    {
        integer_result<byte> result{operand1 & operand2};
        output<byte> output{result.value};
        output.status[flag_type::zero] = result.value == 0;
        output.status[flag_type::subtract] = false;
        output.status[flag_type::half_carry] = true;
        output.status[flag_type::carry] = false;

        return output;
    }

    alu::output<byte> alu::xor_byte(byte operand1, byte operand2) const
    {
        integer_result<byte> result{operand1 ^ operand2};
        output<byte> output{result.value};
        output.status[flag_type::zero] = result.value == 0;
        output.status[flag_type::subtract] = false;
        output.status[flag_type::half_carry] = false;
        output.status[flag_type::carry] = false;

        return output;
    }

    alu::output<byte> alu::or_byte(byte operand1, byte operand2) const
    {
        integer_result<byte> result{operand1 | operand2};
        output<byte> output{result.value};
        output.status[flag_type::zero] = result.value == 0;
        output.status[flag_type::subtract] = false;
        output.status[flag_type::half_carry] = false;
        output.status[flag_type::carry] = false;

        return output;
    }

    alu::output<byte> alu::daa(byte number, const flags& flag) const
    {
        auto adjustment = 0;
        bool has_carry = false;

        if (flag[flag_type::half_carry] || number % 16 > 0x09) {
            adjustment += 0x06;
        }

        if (flag[flag_type::carry] || number > 0x99) {
            adjustment += 0x60;
            has_carry = true;
        }

        if (flag[flag_type::subtract]) {
            adjustment = 0 - adjustment;
        }

        integer_result<byte> result{number + adjustment};
        output<byte> output{result.value};
        output.status[flag_type::zero] = result.value == 0;
        output.status[flag_type::half_carry] = false;
        output.status[flag_type::carry] = has_carry;

        return output;
    }

    template alu::output<byte> alu::add(byte, byte, bool) const;
    template alu::output<signed char> alu::add(signed char, signed char, bool) const;
    template alu::output<unsigned short> alu::add(unsigned short, unsigned short, bool) const;
    template alu::output<short> alu::add(short, short, bool) const;
    template alu::output<byte> alu::subtract(byte, byte, bool) const;
    template alu::output<signed char> alu::subtract(signed char, signed char, bool) const;
    template alu::output<unsigned short> alu::subtract(unsigned short, unsigned short, bool) const;
    template alu::output<short> alu::subtract(short, short, bool) const;
}