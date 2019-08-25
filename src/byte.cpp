#include "byte.h"

namespace gameboy {
    int make_address(byte high, byte low)
    {
        // little-endian implementation
        return (low << 8) | high;
    }
}