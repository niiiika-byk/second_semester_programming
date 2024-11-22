cmake_minimum_required(VERSION 3.10)
project(laba3)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем флаги для покрытия кода (GCov или Clang)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

aux_source_directory(. SOURCES)

add_executable(array_testing array_testing.cpp Array.hpp)
add_executable(list_testing list_testing.cpp List.hpp)
add_executable(2list_testing 2list_testing.cpp List.hpp)
add_executable(stack_testing stack_testing.cpp Stack.hpp)

target_link_libraries(array_testing  ${GTEST_LIBRARIES} pthread)
target_link_libraries(list_testing ${GTEST_LIBRARIES} pthread)
target_link_libraries(2list_testing ${GTEST_LIBRARIES} pthread)
target_link_libraries(stack_testing ${GTEST_LIBRARIES} pthread)

install(TARGETS array_testing DESTINATION bin)
install(TARGETS list_testing DESTINATION bin)
install(TARGETS 2list_testing DESTINATION bin)
install(TARGETS stack_testing DESTINATION bin)

enable_testing()
add_test(test1 ./array_testing)
add_test(test2 ./list_testing)
add_test(test3 ./2list_testing)
add_test(test4 ./stack_testing)

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
    COMMAND genhtml coverage.info --output-directory out
    DEPENDS coverage
    COMMENT "Generating coverage report"
)