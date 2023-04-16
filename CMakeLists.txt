cmake_minimum_required(VERSION 3.14)

include(cmake/toolchain.cmake)
include(cmake/rapidjson.cmake)
include(cmake/fmt.cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

project(genetic_algorithm LANGUAGES C CXX)

add_compile_options(-Wall -Wextra -Wpedantic -Werror $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(app)

file(COPY parameters.json DESTINATION ${CMAKE_BINARY_DIR}/bin)
