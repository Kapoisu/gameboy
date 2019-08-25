#ifndef WORD_H
#define WORD_H

#include "byte.h"

namespace gameboy {
    union word {
    private:
        struct two_bytes {
            byte low;
            byte high;
        };
    public:
        word();
        explicit word(byte low, byte high);

        two_bytes bytes;
        unsigned short value;
    };
}

#endif