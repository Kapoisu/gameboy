#include "memory.h"

namespace gameboy {
    unsigned char memory::get_byte(int address) const
    {
        return _data[address];
    }

    void memory::set_byte(int address, byte value)
    {
        _data[address] = value;
    }
}