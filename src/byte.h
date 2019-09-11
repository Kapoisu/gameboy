#ifndef BYTE_H_
#define BYTE_H_

namespace gameboy {
    using byte = unsigned char;
    using sbyte = signed char;

    int make_address(byte high, byte low);
}

#endif