#include "alu-test.h"
#include <array>
#include <chrono>
#include <future>
#include <iostream>
#include <iomanip>
#include <limits>
#include <typeinfo>

namespace gameboy {
    template<typename T>
    bool alu_test::test_addition() const
    {
        constexpr auto min = std::numeric_limits<T>::min() + 0;
        constexpr auto max = std::numeric_limits<T>::max() + 1;

        auto failed = 0;
        for (auto i = min; i < max; ++i) {
            for (auto j = i; j < max; ++j) {
                const auto op1 = static_cast<T>(i), op2 = static_cast<T>(j);
                const auto output1 = _alu.add(op1, op2);
                const auto output2 = static_cast<T>(op1 + op2);
                const auto value_failed = output1.result != output2;
                const auto zf_failed = output1.status.template is_set<flag_type::zero>() ^ (output2 == 0);
                const auto nf_failed = output1.status.template is_set<flag_type::subtract>() ^ false;
                const auto hf_failed = output1.status.template is_set<flag_type::half_carry>()
                    ^ std::bitset<sizeof(T) * 8>(op1 ^ op2 ^ output2)[sizeof(T) * 8 / 2];
                const auto cf_failed = output1.status.template is_set<flag_type::carry>()
                    ^ std::bitset<sizeof(T) * 8 + 1>(op1 ^ op2 ^ (op1 + op2))[sizeof(T) * 8];
                failed += value_failed || zf_failed || nf_failed || hf_failed || cf_failed;
            }
        }

        std::cout << "Test Addition<" << typeid(T).name() << ">: failed = " << failed << std::endl;

        return failed == 0;
    }

    template<typename T>
    bool alu_test::test_subtraction() const
    {
        constexpr auto max = std::numeric_limits<T>::max() + 1;
        constexpr auto min = std::numeric_limits<T>::min() + 0;

        auto failed = 0;
        for (auto i = min; i < max; ++i) {
            for (auto j = i; j < max; ++j) {
                const auto op1 = static_cast<T>(i), op2 = static_cast<T>(j);
                const auto output1 = _alu.subtract(op1, op2);
                const auto output2 = static_cast<T>(op1 - op2);
                const auto value_failed = output1.result != output2;
                const auto zf_failed = output1.status.template is_set<flag_type::zero>() ^ (output2 == 0);
                const auto nf_failed = output1.status.template is_set<flag_type::subtract>() ^ true;
                const auto hf_failed = output1.status.template is_set<flag_type::half_carry>()
                    ^ std::bitset<sizeof(T) * 8>(op1 ^ op2 ^ output2)[sizeof(T) * 8 / 2];
                const auto cf_failed = output1.status.template is_set<flag_type::carry>()
                    ^ std::bitset<sizeof(T) * 8 + 1>(op1 ^ op2 ^ (op1 - op2))[sizeof(T) * 8];
                failed += value_failed || zf_failed || nf_failed || hf_failed || cf_failed;
            }
        }

        std::cout << "Test Subtraction<" << typeid(T).name() << ">: failed = " << failed << std::endl;

        return failed == 0;
    }

    template bool alu_test::test_addition<byte>() const;
    template bool alu_test::test_addition<signed char>() const;
    template bool alu_test::test_addition<unsigned short>() const;
    template bool alu_test::test_addition<short>() const;
    template bool alu_test::test_subtraction<byte>() const;
    template bool alu_test::test_subtraction<signed char>() const;
    template bool alu_test::test_subtraction<unsigned short>() const;
    template bool alu_test::test_subtraction<short>() const;
}