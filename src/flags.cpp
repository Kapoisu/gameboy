#include "flags.h"

namespace gameboy {
    std::unordered_map<flag_type, int> flags::_flag_map = {
        {flag_type::zero, 7},
        {flag_type::subtract, 6},
        {flag_type::half_carry, 5},
        {flag_type::carry, 4}
    };

    flags::flags() = default;

    flags::flags(byte value) : _flags(value)
    {
    }

    flags& flags::operator=(byte value)
    {
        _flags = value;
        return *this;
    }

    bool flags::operator[](flag_type type) const
    {
        return _flags[_flag_map[type]];
    }

    std::bitset<8>::reference flags::operator[](flag_type type)
    {
        return _flags[_flag_map[type]];
    }

    flags::operator byte() const
    {
        return static_cast<byte>(_flags.to_ulong());
    }
}