#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <limits>
#include "byte.h"

namespace gameboy {
    class memory {
    public:
        unsigned char get_byte(int address) const;
        void set_byte(int address, byte value);
    private:
        std::array<byte, std::numeric_limits<unsigned short>::max() - std::numeric_limits<unsigned short>::min() + 1> _data;
    };
}

#endif