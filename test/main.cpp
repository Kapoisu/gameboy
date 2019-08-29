#include <chrono>
#include <iostream>
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
    alu_test test_alu;
    cpu_test test_cpu{test_memory};

    ++result[test_alu.test_addition<byte>()];
    ++result[test_alu.test_addition<signed char>()];
    ++result[test_alu.test_subtraction<byte>()];
    ++result[test_alu.test_subtraction<signed char>()];
#ifdef TIME_CONSUMING
    ++result[test_alu.test_addition<unsigned short>()];
    ++result[test_alu.test_addition<short>()];
    ++result[test_alu.test_subtraction<unsigned short>()];
    ++result[test_alu.test_subtraction<short>()];
#endif

    std::cout << "Test count: " << result[true] + result[false] << std::endl;
    std::cout << "Test passed: " << result[true] << std::endl;;

    std::cin.get();

    return 0;
}