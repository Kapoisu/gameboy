#include "cpu.h"

namespace gameboy {
    cpu::cpu(memory& mem) : _memory(mem), _cycle(0)
    {
        _instruction_map['\x00'] = [this, cycle = 4] {
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 00 0001 n n
        _instruction_map['\x01'] = [this, cycle = 12] {
            _registers.general_c = _memory.get_byte(_registers.program_counter++);
            _registers.general_b = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00000010
        _instruction_map['\x02'] = [this, cycle = 8] {
            const auto address = _registers.general_bc;
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 000 110 n
        _instruction_map['\x06'] = [this, cycle = 8] {
            _registers.general_b = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00001010
        _instruction_map['\x0A'] = [this, cycle = 8] {
            const auto address = _registers.general_bc;
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 001 110 n
        _instruction_map['\x0E'] = [this, cycle = 8] {
            _registers.general_c = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 01 0001 n n
        _instruction_map['\x11'] = [this, cycle = 12] {
            _registers.general_e = _memory.get_byte(_registers.program_counter++);
            _registers.general_d = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00010010
        _instruction_map['\x12'] = [this, cycle = 8] {
            const auto address = _registers.general_de;
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 010 110 n
        _instruction_map['\x16'] = [this, cycle = 8] {
            _registers.general_d = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00011010
        _instruction_map['\x1A'] = [this, cycle = 8] {
            const auto address = _registers.general_de;
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 011 110 n
        _instruction_map['\x1E'] = [this, cycle = 8] {
            _registers.general_e = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 10 0001 n n
        _instruction_map['\x21'] = [this, cycle = 12] {
            _registers.general_l = _memory.get_byte(_registers.program_counter++);
            _registers.general_h = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LDI 00100010
        _instruction_map['\x22'] = [this, cycle = 8] {
            const auto address = _registers.general_hl++;
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 100 110 n
        _instruction_map['\x26'] = [this, cycle = 8] {
            _registers.general_h = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LDI 00101010
        _instruction_map['\x2A'] = [this, cycle = 8] {
            const auto address = _registers.general_hl++;
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 101 110 n
        _instruction_map['\x2E'] = [this, cycle = 8] {
            _registers.general_l = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 11 0001 n n
        _instruction_map['\x31'] = [this, cycle = 12] {
            const auto low = _memory.get_byte(_registers.program_counter++);
            const auto high = _memory.get_byte(_registers.program_counter++);
            _registers.stack_pointer = word(low, high).value;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LDD 00110010
        _instruction_map['\x32'] = [this, cycle = 8] {
            const auto address = _registers.general_hl--;
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00110110 n
        _instruction_map['\x36'] = [this, cycle = 12] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _memory.get_byte(_registers.program_counter++));
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LDD 00111010
        _instruction_map['\x3A'] = [this, cycle = 8] {
            const auto address = _registers.general_hl--;
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 00 111 110 n
        _instruction_map['\x3E'] = [this, cycle = 8] {
            _registers.accumulator = _memory.get_byte(_registers.program_counter++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 000
        _instruction_map['\x40'] = [this, cycle = 4] {
            _registers.general_b = _registers.general_b;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 001
        _instruction_map['\x41'] = [this, cycle = 4] {
            _registers.general_b = _registers.general_c;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 010
        _instruction_map['\x42'] = [this, cycle = 4] {
            _registers.general_b = _registers.general_d;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 011
        _instruction_map['\x43'] = [this, cycle = 4] {
            _registers.general_b = _registers.general_e;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 100
        _instruction_map['\x44'] = [this, cycle = 4] {
            _registers.general_b = _registers.general_h;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 101
        _instruction_map['\x45'] = [this, cycle = 4] {
            _registers.general_b = _registers.general_l;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 110
        _instruction_map['\x46'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _registers.general_b = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 000 111
        _instruction_map['\x47'] = [this, cycle = 4] {
            _registers.general_b = _registers.accumulator;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 000
        _instruction_map['\x48'] = [this, cycle = 4] {
            _registers.general_c = _registers.general_b;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 001
        _instruction_map['\x49'] = [this, cycle = 4] {
            _registers.general_c = _registers.general_c;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 010
        _instruction_map['\x4A'] = [this, cycle = 4] {
            _registers.general_c = _registers.general_d;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 011
        _instruction_map['\x4B'] = [this, cycle = 4] {
            _registers.general_c = _registers.general_e;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 100
        _instruction_map['\x4C'] = [this, cycle = 4] {
            _registers.general_c = _registers.general_h;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 101
        _instruction_map['\x4D'] = [this, cycle = 4] {
            _registers.general_c = _registers.general_l;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 110
        _instruction_map['\x4E'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _registers.general_c = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 001 111
        _instruction_map['\x4F'] = [this, cycle = 4] {
            _registers.general_c = _registers.accumulator;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 000
        _instruction_map['\x50'] = [this, cycle = 4] {
            _registers.general_d = _registers.general_b;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 001
        _instruction_map['\x51'] = [this, cycle = 4] {
            _registers.general_d = _registers.general_c;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 010
        _instruction_map['\x52'] = [this, cycle = 4] {
            _registers.general_d = _registers.general_d;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 011
        _instruction_map['\x53'] = [this, cycle = 4] {
            _registers.general_d = _registers.general_e;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 100
        _instruction_map['\x54'] = [this, cycle = 4] {
            _registers.general_d = _registers.general_h;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 101
        _instruction_map['\x55'] = [this, cycle = 4] {
            _registers.general_d = _registers.general_l;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 110
        _instruction_map['\x56'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _registers.general_d = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 010 111
        _instruction_map['\x57'] = [this, cycle = 4] {
            _registers.general_d = _registers.accumulator;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 000
        _instruction_map['\x58'] = [this, cycle = 4] {
            _registers.general_e = _registers.general_b;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 001
        _instruction_map['\x59'] = [this, cycle = 4] {
            _registers.general_e = _registers.general_c;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 010
        _instruction_map['\x5A'] = [this, cycle = 4] {
            _registers.general_e = _registers.general_d;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 011
        _instruction_map['\x5B'] = [this, cycle = 4] {
            _registers.general_e = _registers.general_e;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 100
        _instruction_map['\x5C'] = [this, cycle = 4] {
            _registers.general_e = _registers.general_h;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 101
        _instruction_map['\x5D'] = [this, cycle = 4] {
            _registers.general_e = _registers.general_l;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 110
        _instruction_map['\x5E'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _registers.general_e = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 011 111
        _instruction_map['\x5F'] = [this, cycle = 4] {
            _registers.general_e = _registers.accumulator;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 000
        _instruction_map['\x60'] = [this, cycle = 4] {
            _registers.general_h = _registers.general_b;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 001
        _instruction_map['\x61'] = [this, cycle = 4] {
            _registers.general_h = _registers.general_c;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 010
        _instruction_map['\x62'] = [this, cycle = 4] {
            _registers.general_h = _registers.general_d;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 011
        _instruction_map['\x63'] = [this, cycle = 4] {
            _registers.general_h = _registers.general_e;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 100
        _instruction_map['\x64'] = [this, cycle = 4] {
            _registers.general_h = _registers.general_h;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 101
        _instruction_map['\x65'] = [this, cycle = 4] {
            _registers.general_h = _registers.general_l;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 110
        _instruction_map['\x66'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _registers.general_h = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 100 111
        _instruction_map['\x67'] = [this, cycle = 4] {
            _registers.general_h = _registers.accumulator;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 000
        _instruction_map['\x68'] = [this, cycle = 4] {
            _registers.general_l = _registers.general_b;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 001
        _instruction_map['\x69'] = [this, cycle = 4] {
            _registers.general_l = _registers.general_c;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 010
        _instruction_map['\x6A'] = [this, cycle = 4] {
            _registers.general_l = _registers.general_d;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 011
        _instruction_map['\x6B'] = [this, cycle = 4] {
            _registers.general_l = _registers.general_e;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 100
        _instruction_map['\x6C'] = [this, cycle = 4] {
            _registers.general_l = _registers.general_h;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 101
        _instruction_map['\x6D'] = [this, cycle = 4] {
            _registers.general_l = _registers.general_l;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 110
        _instruction_map['\x6E'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _registers.general_l = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 101 111
        _instruction_map['\x6F'] = [this, cycle = 4] {
            _registers.general_l = _registers.accumulator;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01110 000
        _instruction_map['\x70'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _registers.general_b);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01110 001
        _instruction_map['\x71'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _registers.general_c);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01110 010
        _instruction_map['\x72'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _registers.general_d);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01110 011
        _instruction_map['\x73'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _registers.general_e);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01110 100
        _instruction_map['\x74'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _registers.general_h);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01110 101
        _instruction_map['\x75'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _registers.general_l);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01110 111
        _instruction_map['\x77'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 000
        _instruction_map['\x78'] = [this, cycle = 4] {
            _registers.accumulator = _registers.general_b;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 001
        _instruction_map['\x79'] = [this, cycle = 4] {
            _registers.accumulator = _registers.general_c;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 010
        _instruction_map['\x7A'] = [this, cycle = 4] {
            _registers.accumulator = _registers.general_d;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 011
        _instruction_map['\x7B'] = [this, cycle = 4] {
            _registers.accumulator = _registers.general_e;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 100
        _instruction_map['\x7C'] = [this, cycle = 4] {
            _registers.accumulator = _registers.general_h;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 101
        _instruction_map['\x7D'] = [this, cycle = 4] {
            _registers.accumulator = _registers.general_l;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 110
        _instruction_map['\x7E'] = [this, cycle = 8] {
            const auto address = _registers.general_hl;
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 01 111 111
        _instruction_map['\x7F'] = [this, cycle = 4] {
            _registers.accumulator = _registers.accumulator;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000 000
        _instruction_map['\x80'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_b);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000 001
        _instruction_map['\x81'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_c);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000 010
        _instruction_map['\x82'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_d);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000 011
        _instruction_map['\x83'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_e);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000 100
        _instruction_map['\x84'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_h);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000 101
        _instruction_map['\x85'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_l);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000110
        _instruction_map['\x86'] = [this, cycle = 8] {
            const auto output = _alu.add(_registers.accumulator, _memory.get_byte(_registers.general_hl));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 10000 111
        _instruction_map['\x87'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.accumulator);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001 000
        _instruction_map['\x88'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_b, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001 001
        _instruction_map['\x89'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_c, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001 010
        _instruction_map['\x8A'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_d, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001 011
        _instruction_map['\x8B'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_e, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001 100
        _instruction_map['\x8C'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_h, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001 101
        _instruction_map['\x8D'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.general_l, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001110
        _instruction_map['\x8E'] = [this, cycle = 8] {
            const auto output = _alu.add(_registers.accumulator, _memory.get_byte(_registers.general_hl),
                _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 10001 111
        _instruction_map['\x8F'] = [this, cycle = 4] {
            const auto output = _alu.add(_registers.accumulator, _registers.accumulator, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010 000
        _instruction_map['\x90'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_b);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010 001
        _instruction_map['\x91'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_c);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010 010
        _instruction_map['\x92'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_d);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010 011
        _instruction_map['\x93'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_e);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010 100
        _instruction_map['\x94'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_h);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010 101
        _instruction_map['\x95'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_l);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010110
        _instruction_map['\x96'] = [this, cycle = 8] {
            const auto output = _alu.subtract(_registers.accumulator, _memory.get_byte(_registers.general_hl));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 10010 111
        _instruction_map['\x97'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.accumulator);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011 000
        _instruction_map['\x98'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_b, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011 001
        _instruction_map['\x99'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_c, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011 010
        _instruction_map['\x9A'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_d, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011 011
        _instruction_map['\x9B'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_e, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011 100
        _instruction_map['\x9C'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_h, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011 101
        _instruction_map['\x9D'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_l, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011110
        _instruction_map['\x9E'] = [this, cycle = 8] {
            const auto output = _alu.subtract(_registers.accumulator, _memory.get_byte(_registers.general_hl),
                _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 10011 111
        _instruction_map['\x9F'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.accumulator, _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100 000
        _instruction_map['\xA0'] = [this, cycle = 4] {
            const auto output = _alu.and_byte(_registers.accumulator, _registers.general_b);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100 001
        _instruction_map['\xA1'] = [this, cycle = 4] {
            const auto output = _alu.and_byte(_registers.accumulator, _registers.general_c);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100 010
        _instruction_map['\xA2'] = [this, cycle = 4] {
            const auto output = _alu.and_byte(_registers.accumulator, _registers.general_d);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100 011
        _instruction_map['\xA3'] = [this, cycle = 4] {
            const auto output = _alu.and_byte(_registers.accumulator, _registers.general_e);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100 100
        _instruction_map['\xA4'] = [this, cycle = 4] {
            const auto output = _alu.and_byte(_registers.accumulator, _registers.general_h);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100 101
        _instruction_map['\xA5'] = [this, cycle = 4] {
            const auto output = _alu.and_byte(_registers.accumulator, _registers.general_l);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100110
        _instruction_map['\xA6'] = [this, cycle = 8] {
            const auto output = _alu.and_byte(_registers.accumulator, _memory.get_byte(_registers.general_hl));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 10100 111
        _instruction_map['\xA7'] = [this, cycle = 4] {
            const auto output = _alu.and_byte(_registers.accumulator, _registers.accumulator);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101 000
        _instruction_map['\xA8'] = [this, cycle = 4] {
            const auto output = _alu.xor_byte(_registers.accumulator, _registers.general_b);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101 001
        _instruction_map['\xA9'] = [this, cycle = 4] {
            const auto output = _alu.xor_byte(_registers.accumulator, _registers.general_c);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101 010
        _instruction_map['\xAA'] = [this, cycle = 4] {
            const auto output = _alu.xor_byte(_registers.accumulator, _registers.general_d);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101 011
        _instruction_map['\xAB'] = [this, cycle = 4] {
            const auto output = _alu.xor_byte(_registers.accumulator, _registers.general_e);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101 100
        _instruction_map['\xAC'] = [this, cycle = 4] {
            const auto output = _alu.xor_byte(_registers.accumulator, _registers.general_h);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101 101
        _instruction_map['\xAD'] = [this, cycle = 4] {
            const auto output = _alu.xor_byte(_registers.accumulator, _registers.general_l);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101110
        _instruction_map['\xAE'] = [this, cycle = 8] {
            const auto output = _alu.xor_byte(_registers.accumulator, _memory.get_byte(_registers.general_hl));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 10101 111
        _instruction_map['\xAF'] = [this, cycle = 4] {
            const auto output = _alu.xor_byte(_registers.accumulator, _registers.accumulator);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110 000
        _instruction_map['\xB0'] = [this, cycle = 4] {
            const auto output = _alu.or_byte(_registers.accumulator, _registers.general_b);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110 001
        _instruction_map['\xB1'] = [this, cycle = 4] {
            const auto output = _alu.or_byte(_registers.accumulator, _registers.general_c);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110 010
        _instruction_map['\xB2'] = [this, cycle = 4] {
            const auto output = _alu.or_byte(_registers.accumulator, _registers.general_d);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110 011
        _instruction_map['\xB3'] = [this, cycle = 4] {
            const auto output = _alu.or_byte(_registers.accumulator, _registers.general_e);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110 100
        _instruction_map['\xB4'] = [this, cycle = 4] {
            const auto output = _alu.or_byte(_registers.accumulator, _registers.general_h);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110 101
        _instruction_map['\xB5'] = [this, cycle = 4] {
            const auto output = _alu.or_byte(_registers.accumulator, _registers.general_l);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110110
        _instruction_map['\xB6'] = [this, cycle = 8] {
            const auto output = _alu.or_byte(_registers.accumulator, _memory.get_byte(_registers.general_hl));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 10110 111
        _instruction_map['\xB7'] = [this, cycle = 4] {
            const auto output = _alu.or_byte(_registers.accumulator, _registers.accumulator);
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111 000
        _instruction_map['\xB8'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_b);
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111 001
        _instruction_map['\xB9'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_c);
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111 010
        _instruction_map['\xBA'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_d);
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111 011
        _instruction_map['\xBB'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_e);
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111 100
        _instruction_map['\xBC'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_h);
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111 101
        _instruction_map['\xBD'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.general_l);
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111110
        _instruction_map['\xBE'] = [this, cycle = 8] {
            const auto output = _alu.subtract(_registers.accumulator, _memory.get_byte(_registers.general_hl));
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 10111 111
        _instruction_map['\xBF'] = [this, cycle = 4] {
            const auto output = _alu.subtract(_registers.accumulator, _registers.accumulator);
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // POP 11 00 0001
        _instruction_map['\xC1'] = [this, cycle = 12] {
            _registers.general_c = _memory.get_byte(_registers.stack_pointer++);
            _registers.general_b = _memory.get_byte(_registers.stack_pointer++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // PUSH 11 00 0101
        _instruction_map['\xC5'] = [this, cycle = 16] {
            _memory.set_byte(--_registers.stack_pointer, _registers.general_b);
            _memory.set_byte(--_registers.stack_pointer, _registers.general_c);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADD 11000110 n
        _instruction_map['\xC6'] = [this, cycle = 8] {
            const auto output = _alu.add(_registers.accumulator, _memory.get_byte(_registers.program_counter++));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // ADC 11001110 n
        _instruction_map['\xCE'] = [this, cycle = 8] {
            const auto output = _alu.add(_registers.accumulator, _memory.get_byte(_registers.program_counter++),
                _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // POP 11 01 0001
        _instruction_map['\xD1'] = [this, cycle = 12] {
            _registers.general_e = _memory.get_byte(_registers.stack_pointer++);
            _registers.general_d = _memory.get_byte(_registers.stack_pointer++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // PUSH 11 01 0101
        _instruction_map['\xD5'] = [this, cycle = 16] {
            _memory.set_byte(--_registers.stack_pointer, _registers.general_d);
            _memory.set_byte(--_registers.stack_pointer, _registers.general_e);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SUB 11010110 n
        _instruction_map['\xD6'] = [this, cycle = 8] {
            const auto output = _alu.subtract(_registers.accumulator, _memory.get_byte(_registers.program_counter++));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // SBC 11011110 n
        _instruction_map['\xDE'] = [this, cycle = 8] {
            const auto output = _alu.subtract(_registers.accumulator, _memory.get_byte(_registers.program_counter++),
                _registers.flag.is_set<flag_type::carry>());
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 11100000 n
        _instruction_map['\xE0'] = [this, cycle = 12] {
            const auto address = make_address('\xFF', _memory.get_byte(_registers.program_counter++));
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // POP 11 10 0001
        _instruction_map['\xE1'] = [this, cycle = 12] {
            _registers.general_l = _memory.get_byte(_registers.stack_pointer++);
            _registers.general_h = _memory.get_byte(_registers.stack_pointer++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 11100010
        _instruction_map['\xE2'] = [this, cycle = 8] {
            const auto address = make_address('\xFF', _registers.general_c);
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // PUSH 11 10 0101
        _instruction_map['\xE5'] = [this, cycle = 16] {
            _memory.set_byte(--_registers.stack_pointer, _registers.general_h);
            _memory.set_byte(--_registers.stack_pointer, _registers.general_l);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // AND 11000110 n
        _instruction_map['\xE6'] = [this, cycle = 8] {
            const auto output = _alu.and_byte(_registers.accumulator, _memory.get_byte(_registers.program_counter++));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 11101010 (nn)
        _instruction_map['\xEA'] = [this, cycle = 16] {
            const auto low = _memory.get_byte(_registers.program_counter++);
            const auto high = _memory.get_byte(_registers.program_counter++);
            const auto address = make_address(high, low);
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // XOR 11101110 n
        _instruction_map['\xEE'] = [this, cycle = 8] {
            const auto output = _alu.xor_byte(_registers.accumulator, _memory.get_byte(_registers.program_counter++));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 11110000 n
        _instruction_map['\xF0'] = [this, cycle = 12] {
            const auto address = make_address('\xFF', _memory.get_byte(_registers.program_counter++));
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // POP 11 11 0001
        _instruction_map['\xF1'] = [this, cycle = 12] {
            _registers.flag = _memory.get_byte(_registers.stack_pointer++);
            _registers.accumulator = _memory.get_byte(_registers.stack_pointer++);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 11110010
        _instruction_map['\xF2'] = [this, cycle = 8] {
            const auto address = make_address('\xFF', _registers.general_c);
            _memory.set_byte(address, _registers.accumulator);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // PUSH 11 11 0101
        _instruction_map['\xF5'] = [this, cycle = 16] {
            _memory.set_byte(--_registers.stack_pointer, _registers.accumulator);
            _memory.set_byte(--_registers.stack_pointer, _registers.flag);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // OR 11110110 n
        _instruction_map['\xF6'] = [this, cycle = 8] {
            const auto output = _alu.or_byte(_registers.accumulator, _memory.get_byte(_registers.program_counter++));
            _registers.accumulator = output.result;
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 11111001
        _instruction_map['\xF9'] = [this, cycle = 8] {
            _registers.stack_pointer = _registers.general_hl;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // LD 11111010 (nn)
        _instruction_map['\xFA'] = [this, cycle = 16] {
            const auto low = _memory.get_byte(_registers.program_counter++);
            const auto high = _memory.get_byte(_registers.program_counter++);
            const auto address = make_address(high, low);
            _registers.accumulator = _memory.get_byte(address);
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };

        // CP 11111110 n
        _instruction_map['\xFE'] = [this, cycle = 8] {
            const auto output = _alu.subtract(_registers.accumulator, _memory.get_byte(_registers.program_counter++));
            _registers.flag = output.status;
            _cycle = (_cycle + cycle) % CYCLES_PER_FRAME;
        };
    }

    void cpu::fetch()
    {
        const auto opcode = _memory.get_byte(_registers.program_counter++);

        _instruction_map[opcode]();
    }
}