cmake_minimum_required(VERSION 3.14)

set(EXECUTABLE_NAME genetic_algorithm${EXE_EXTENSION})

add_executable(${EXECUTABLE_NAME}
        Population.cpp
        parameters.cpp
        dump.cpp
        main.cpp
        )

target_link_libraries(${EXECUTABLE_NAME}
        PUBLIC fmt rapidjson
        )
