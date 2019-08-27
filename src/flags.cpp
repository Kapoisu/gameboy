#include "flags.h"

namespace gameboy {
    std::map<flag_type, int> flags::_flag_map = {
        {flag_type::ZERO, 7},
        {flag_type::ADD_SUB, 6},
        {flag_type::HALF_CARRY, 5},
        {flag_type::CARRY, 4}
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

    flags::operator byte() const
    {
        return static_cast<byte>(_flags.to_ulong());
    }
}