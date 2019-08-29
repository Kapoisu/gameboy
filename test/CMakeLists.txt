add_executable(gameboy-test main.cpp alu-test.cpp cpu-test.cpp)
add_executable(gameboy-test-full main.cpp alu-test.cpp cpu-test.cpp)

target_include_directories(gameboy-test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(gameboy-test-full PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(gameboy-test PRIVATE gameboy)
target_link_libraries(gameboy-test-full PRIVATE gameboy)

target_compile_definitions(gameboy-test-full PRIVATE TIME_CONSUMING)