cmake_minimum_required(VERSION 3.14)

set(EXECUTABLE_NAME test${EXE_EXTENSION})

add_executable(${EXECUTABLE_NAME}
        test.cpp
        )

if (USE_SAN)
        add_sanitizers(${EXECUTABLE_NAME})
endif()

target_link_libraries(${EXECUTABLE_NAME}
        PUBLIC Catch2::Catch2WithMain fmt genixx::chromosome genixx::population genixx::error genixx::utils
        )
