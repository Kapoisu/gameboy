#ifndef FLAGS_H
#define FLAGS_H

#include <bitset>
#include <unordered_map>
#include "byte.h"

namespace gameboy {
    enum class flag_type {
        zero,
        subtract,
        half_carry,
        carry
    };

    class flags {
    public:
        flags();
        explicit flags(byte value);
        flags& operator=(byte value);
        operator byte() const;

        template<flag_type T>
        void set(bool flag)
        {
            _flags.set(_flag_map[T], flag);
        }

        template<flag_type T>
        bool is_set() const
        {
            return _flags[_flag_map[T]];
        }
    private:
        static std::unordered_map<flag_type, int> _flag_map;
        std::bitset<8> _flags;
    };
}

#endif