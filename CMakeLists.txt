cmake_minimum_required(VERSION 3.13)
project(ChipmosAPS LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(MSVC)
    add_compile_options(
        /Wall /WX 
        /fsanitize=address 
        /fsanitize=fuzzer
    )
else()
    
    add_compile_options(
        -Wall -Wextra -Wpedantic -Werror
        -fsanitize=address
    )
    add_link_options(-fsanitize=address)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(scripts)