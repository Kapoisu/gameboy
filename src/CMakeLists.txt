add_executable(gameboy main.cpp cpu.cpp registers.cpp memory.cpp byte.cpp word.cpp)

target_link_libraries(gameboy PRIVATE pthread)