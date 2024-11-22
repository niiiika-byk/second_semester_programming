cmake_minimum_required(VERSION 3.10)
project(laba3)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add flags for coverage
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# List of test executables and their source files
set(TEST_EXECUTABLES
    array_testing.cpp
    list_testing.cpp
    2list_testing.cpp
    stack_testing.cpp
    queue_testing.cpp
)

# Add executables and link GTest
foreach(TEST ${TEST_EXECUTABLES})
    get_filename_component(TEST_NAME ${TEST} NAME_WE)  # Get the name without extension
    add_executable(${TEST_NAME} ${TEST})
    target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} pthread)
    install(TARGETS ${TEST_NAME} DESTINATION bin)
endforeach()

enable_testing()
foreach(TEST ${TEST_EXECUTABLES})
    get_filename_component(TEST_NAME ${TEST} NAME_WE)  # Get the name without extension
    add_test(NAME ${TEST_NAME} COMMAND ./${TEST_NAME})
endforeach()

# Coverage target
add_custom_target(
    coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --coverage --output-on-failure
    DEPENDS ${TEST_EXECUTABLES}
)

# Coverage report
add_custom_target(
    gen_coverage_report
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory out
    DEPENDS coverage
    COMMENT "Generating coverage report"
)