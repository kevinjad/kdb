cmake_minimum_required(VERSION 3.16)
project(kdb)
add_compile_options (-std=c++14)

set(CMAKE_CXX_STANDARD 14)

include_directories (lib/libelfin lib/linenoise include)
add_executable (kdb lib/linenoise/linenoise.c src/kdb.cpp src/Debugger.cpp include/Debugger.h src/Breakpoint.cpp include/Breakpoint.h src/registers.cpp include/registers.h)

add_executable(hello examples/hello.cpp)
set_target_properties(hello PROPERTIES COMPILE_FLAGS "-g -O0")

add_executable(variable examples/variable.cpp)
set_target_properties(variable PROPERTIES COMPILE_FLAGS "-gdwarf-2 -O0")

add_executable(unwinding examples/stack_unwinding.cpp)
set_target_properties(unwinding PROPERTIES COMPILE_FLAGS "-g -O0")

add_custom_target(
        libelfin
        COMMAND make
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/libelfin
)
target_link_libraries(kdb
        ${PROJECT_SOURCE_DIR}/lib/libelfin/dwarf/libdwarf++.so
        ${PROJECT_SOURCE_DIR}/lib/libelfin/elf/libelf++.so)
add_dependencies(kdb libelfin)
