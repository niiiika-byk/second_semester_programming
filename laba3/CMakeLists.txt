cmake_minimum_required(VERSION 3.10)
project(laba3)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем флаги для покрытия кода (GCov или Clang)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

aux_source_directory(. SOURCES)

add_executable(main_testing main_testing.cpp Array.hpp List.hpp Queue.hpp hash_function.hpp CB_tree.hpp 
HashTable.hpp Node.hpp hash_node.hpp Stack.hpp tree_node.hpp)

target_link_libraries(main_testing ${GTEST_LIBRARIES} pthread)

install(TARGETS main_testing DESTINATION bin)

enable_testing()
add_test(test ./main_testing)

# Сбор данных покрытия
# параметры для сбора покрытия
add_custom_target(
    coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --coverage --output-on-failure
    DEPENDS test1_app test2_app test3_app test4_app
)

# отчет о покрытии lcov
add_custom_target(
    gen_coverage_report
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory out --ignore-errors mismatch
    DEPENDS coverage
    COMMENT "Generating coverage report"
)