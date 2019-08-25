#include "word.h"

namespace gameboy {
    word::word() = default;

    word::word(byte low, byte high) : bytes({low, high})
    {
    }
}