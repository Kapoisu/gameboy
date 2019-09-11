#include "alu-test.h"
#include <array>
#include <chrono>
#include <future>
#include <iostream>
#include <limits>
#include <typeinfo>

namespace gameboy {
    template<typename T, typename U>
    bool alu_test::test_addition() const
    {
        constexpr auto lower_bound = std::numeric_limits<T>::min() + 0;
        constexpr auto upper_bound = std::numeric_limits<T>::max() + 1;

        auto failed = 0;
        for (auto i = lower_bound; i < upper_bound; ++i) {
            for (auto j = i; j < upper_bound; ++j) {
                const auto op1 = static_cast<T>(i), op2 = static_cast<U>(j);
                const auto output1 = _alu.add(op1, op2);
                const auto output2 = static_cast<T>(op1 + op2);
                const auto value_failed = output1.result != output2;
                const bool zf_failed = output1.status[flag_type::zero] ^ (output2 == 0);
                const bool nf_failed = output1.status[flag_type::subtract] ^ false;
                const bool hf_failed = output1.status[flag_type::half_carry]
                    ^ std::bitset<sizeof(T) * 8>(op1 ^ op2 ^ output2)[sizeof(T) * 8 - 4];
                const bool cf_failed = output1.status[flag_type::carry]
                    ^ std::bitset<sizeof(T) * 8 + 1>(op1 ^ op2 ^ (op1 + op2))[sizeof(T) * 8];
                failed += value_failed || zf_failed || nf_failed || hf_failed || cf_failed;
            }
        }

        std::cout << "Test Addition<" << typeid(T).name() << ">: failed = " << failed << std::endl;

        return failed == 0;
    }

    template<typename T, typename U>
    bool alu_test::test_subtraction() const
    {
        constexpr auto lower_bound = std::numeric_limits<T>::min() + 0;
        constexpr auto upper_bound = std::numeric_limits<T>::max() + 1;

        auto failed = 0;
        for (auto i = lower_bound; i < upper_bound; ++i) {
            for (auto j = i; j < upper_bound; ++j) {
                const auto op1 = static_cast<T>(i), op2 = static_cast<U>(j);
                const auto output1 = _alu.subtract(op1, op2);
                const auto output2 = static_cast<T>(op1 - op2);
                const auto value_failed = output1.result != output2;
                const bool zf_failed = output1.status[flag_type::zero] ^ (output2 == 0);
                const bool nf_failed = output1.status[flag_type::subtract] ^ true;
                const bool hf_failed = output1.status[flag_type::half_carry]
                    ^ std::bitset<sizeof(T) * 8>(op1 ^ op2 ^ output2)[sizeof(T) * 8 - 4];
                const bool cf_failed = output1.status[flag_type::carry]
                    ^ std::bitset<sizeof(T) * 8 + 1>(op1 ^ op2 ^ (op1 - op2))[sizeof(T) * 8];
                failed += value_failed || zf_failed || nf_failed || hf_failed || cf_failed;
            }
        }

        std::cout << "Test Subtraction<" << typeid(T).name() << ">: failed = " << failed << std::endl;

        return failed == 0;
    }

    bool alu_test::test_daa() const
    {
        auto failed = 0;

        for (auto i = 0; i < 100; ++i) {
            for (auto j = 0; j < 100; ++j) {
                const auto op1 = static_cast<byte>(i / 10 * 16 + i % 10);
                const auto op2 = static_cast<byte>(j / 10 * 16 + j % 10);
                const auto non_adjusted = _alu.add(op1, op2);
                const auto adjusted = _alu.daa(non_adjusted.result, non_adjusted.status);
                const auto output1 = adjusted.result / 16 * 10 + adjusted.result % 16;
                const auto output2 = static_cast<byte>(i + j);
                const auto value_failed = output1 != output2 % 100;
                const bool zf_failed = adjusted.status[flag_type::zero] ^ (output2 % 100 == 0);
                const bool hf_failed = adjusted.status[flag_type::half_carry] ^ false;
                const bool cf_failed = adjusted.status[flag_type::carry] ^ (output2 > 99);
                failed += value_failed || zf_failed || hf_failed || cf_failed;
            }
        }

        for (auto i = 0; i < 100; ++i) {
            for (auto j = 0; j < 100; ++j) {
                const auto op1 = static_cast<byte>(i / 10 * 16 + i % 10);
                const auto op2 = static_cast<byte>(j / 10 * 16 + j % 10);
                const auto non_adjusted = _alu.subtract(op1, op2);
                const auto adjusted = _alu.daa(non_adjusted.result, non_adjusted.status);
                const auto output1 = adjusted.result / 16 * 10 + adjusted.result % 16;
                const auto output2 = static_cast<byte>(100 + i - j);
                const auto value_failed = output1 != output2 % 100;
                const bool zf_failed = adjusted.status[flag_type::zero] ^ (output2 % 100 == 0);
                const bool hf_failed = adjusted.status[flag_type::half_carry] ^ false;
                const bool cf_failed = adjusted.status[flag_type::carry] ^ (i < j);
                failed += value_failed || zf_failed || hf_failed || cf_failed;
            }
        }

        std::cout << "Test Decimal Adjustment: failed = " << failed << std::endl;

        return failed == 0;
    }

    template bool alu_test::test_addition<byte, byte>() const;
    template bool alu_test::test_addition<byte, sbyte>() const;
    template bool alu_test::test_addition<sbyte, sbyte>() const;
    template bool alu_test::test_addition<unsigned short, unsigned short>() const;
    template bool alu_test::test_addition<short, short>() const;
    template bool alu_test::test_subtraction<byte, byte>() const;
    template bool alu_test::test_subtraction<byte, sbyte>() const;
    template bool alu_test::test_subtraction<sbyte, sbyte>() const;
    template bool alu_test::test_subtraction<unsigned short, unsigned short>() const;
    template bool alu_test::test_subtraction<short, short>() const;
}