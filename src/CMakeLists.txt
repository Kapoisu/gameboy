add_library(gameboy cpu.cpp registers.cpp memory.cpp byte.cpp word.cpp flags.cpp alu.cpp)

target_link_libraries(gameboy PRIVATE pthread)