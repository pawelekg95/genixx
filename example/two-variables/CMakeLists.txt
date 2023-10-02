cmake_minimum_required(VERSION 3.14)

set(EXECUTABLE_NAME two-variables-example${EXE_EXTENSION})

add_executable(${EXECUTABLE_NAME}
        Chromosome.cpp
        main.cpp
        )

target_link_libraries(${EXECUTABLE_NAME}
        PUBLIC fmt genixx::chromosome genixx::population genixx::error genixx::utils
        )
