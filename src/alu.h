#ifndef ALU_H
#define ALU_H

#include <limits>

namespace gameboy {
    class alu {
    private:
        template<typename T>
        union integer_result {
        public:
            explicit integer_result(int value) : result_with_promotion(value)
            {
            }
            T result;
            int result_with_promotion;
        };
    public:
        template<typename T>
        struct output {
            T result;
            bool is_overflow;
        };

        template<typename T>
        output<T> add(T operand1, T operand2)
        {
            integer_result<T> temp(operand1 + operand2);
            return output<T>({temp.result, temp.result_with_promotion > std::numeric_limits<T>::max()});
        }

        template<typename T>
        output<T> subtract(T operand1, T operand2)
        {
            integer_result<T> temp(operand1 + operand2);
            return output<T>({temp.result, temp.result_with_promotion < 0});
        }
    };
}

#endif