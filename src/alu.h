#ifndef ALU_H
#define ALU_H

#include <limits>
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
            int value_with_promotion;
        };
    public:
        template<typename T>
        struct output {
            T result;
            flags status;
        };

        template<typename T>
        output<T> add(T operand1, T operand2)
        {
            constexpr auto half_mask = (1 << (sizeof(T) * 8 / 2)) - 1;
            integer_result<T> result{operand1 + operand2};
            output<T> output{result.value};
            output.status.template
            set<flag_type::zero>(result.value == 0);
            output.status.template
            set<flag_type::subtract>(false);
            output.status.template
            set<flag_type::half_carry>(((operand1 & half_mask) + (operand2 & half_mask)) > half_mask);
            output.status.template
            set<flag_type::carry>(result.value_with_promotion > std::numeric_limits<T>::max());

            return output;
        }

        template<typename T>
        output<T> subtract(T operand1, T operand2)
        {
            constexpr auto half_mask = (1 << (sizeof(T) * 8 / 2)) - 1;
            integer_result<T> result{operand1 - operand2};
            output<T> output{result.value};
            output.status.template
            set<flag_type::zero>(result.value == 0);
            output.status.template
            set<flag_type::subtract>(true);
            output.status.template
            set<flag_type::half_carry>(((operand1 & half_mask) - (operand2 & half_mask)) < 0);
            output.status.template
            set<flag_type::carry>(result.value_with_promotion < std::numeric_limits<T>::min());

            return output;
        }
    };
}

#endif