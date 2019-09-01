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
        bool operator[](flag_type type) const;
        std::bitset<8>::reference operator[](flag_type type);
        operator byte() const;

        template<bool Z, bool N, bool H, bool C>
        void assign(const flags& value)
        {
            if (Z) {
                _flags.set(_flag_map[flag_type::zero], value[flag_type::zero]);
            }

            if (N) {
                _flags.set(_flag_map[flag_type::subtract], value[flag_type::subtract]);
            }

            if (H) {
                _flags.set(_flag_map[flag_type::half_carry], value[flag_type::half_carry]);
            }

            if (C) {
                _flags.set(_flag_map[flag_type::carry], value[flag_type::carry]);
            }
        }
    private:
        static std::unordered_map<flag_type, int> _flag_map;
        std::bitset<8> _flags;
    };
}

#endif