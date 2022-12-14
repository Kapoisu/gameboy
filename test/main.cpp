#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <thread>
#include <unordered_map>
#include "alu-test.h"
#include "cpu-test.h"

int main()
{
    using namespace gameboy;
    using namespace std::chrono_literals;

    std::unordered_map<bool, int> result;
    memory test_memory;
    std::random_device seed;
    std::default_random_engine generator{seed()};
    constexpr auto lower_bound = std::numeric_limits<unsigned short>::min() + 0;
    constexpr auto upper_bound = std::numeric_limits<unsigned short>::max() + 1;
    std::uniform_int_distribution<int> distribution{lower_bound, upper_bound};
    for (auto address = lower_bound; address < upper_bound; ++address) {
        test_memory.set_byte(address, static_cast<byte>(distribution(generator)));
    }

    alu_test test_alu;
    cpu_test test_cpu{test_memory};

    ++result[test_alu.test_addition<byte, byte>()];
    ++result[test_alu.test_addition<byte, sbyte>()];
    ++result[test_alu.test_addition<sbyte, sbyte>()];
    ++result[test_alu.test_subtraction<byte, byte>()];
    ++result[test_alu.test_subtraction<byte, sbyte>()];
    ++result[test_alu.test_subtraction<sbyte, sbyte>()];
    ++result[test_alu.test_shift_left<byte>()];
    ++result[test_alu.test_shift_left<unsigned short>()];
    ++result[test_alu.test_daa()];
#ifdef TIME_CONSUMING
    ++result[test_alu.test_addition<unsigned short, unsigned short>()];
    ++result[test_alu.test_addition<short, short>()];
    ++result[test_alu.test_subtraction<unsigned short, unsigned short>()];
    ++result[test_alu.test_subtraction<short, short>()];
#endif

    std::cout << "Test count: " << result[true] + result[false] << std::endl;
    std::cout << "Test passed: " << result[true] << std::endl;;

    std::cin.get();

    return 0;
}