#ifndef FLAGS_H
#define FLAGS_H

#include <bitset>
#include <map>
#include "byte.h"

namespace gameboy {
    enum class flag_type {
        ZERO,
        ADD_SUB,
        HALF_CARRY,
        CARRY
    };

    class flags {
    public:
        flags();
        explicit flags(byte value);
        flags& operator=(byte value);
        operator byte() const;

        template<flag_type T>
        void set_flag(bool flag)
        {
            _flags.set(_flag_map[T], flag);
        }

        template<flag_type T>
        bool is_set() const
        {
            return _flags[_flag_map[T]];
        }
    private:
        static std::map<flag_type, int> _flag_map;
        std::bitset<8> _flags;
    };
}

#endif