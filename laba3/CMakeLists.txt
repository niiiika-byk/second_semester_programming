cmake_minimum_required(VERSION 3.10)
project(laba3)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SOURCES)

add_executable(testing ${SOURCES})

install(TARGETS testing DESTINATION bin)
