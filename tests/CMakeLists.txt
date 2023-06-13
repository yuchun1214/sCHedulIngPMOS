set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)



set(TEST_SRC
    test_time_converter.cpp
    test_csv_has_bom.cpp
    test_csv_parse.cpp
    test_csv_read.cpp
    test_is_numeric.cpp
    test_list.cpp
    test_machine_sort_job.cpp
    test_job_base_machine_selection.cpp
)

add_executable(Tests
  main.cpp
  ${TEST_SRC}
)

target_link_libraries(Tests
    PRIVATE
    GTest::GTest
    src
)

add_test(NAME gTests COMMAND Tests)
# gtest_discover_tests(Tests)