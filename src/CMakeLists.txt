set(src_files
    time_converter.cpp
    csv.cpp
    util.cpp
    machine_base.cpp
    job_base.cpp
)

add_library(src STATIC ${src_files})
target_compile_features(src PUBLIC cxx_std_17)
target_include_directories(src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})