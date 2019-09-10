#include "alu.h"

namespace gameboy {
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
}