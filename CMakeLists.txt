cmake_minimum_required(VERSION 3.8)
project(ChipmosAPS LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(MSVC)
    add_compile_options(/Wall /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(scripts)