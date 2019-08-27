#include "word.h"

namespace gameboy {
    word::word() : value(0)
    {
    }

    word::word(byte low, byte high) : bytes({low, high})
    {
    }
}