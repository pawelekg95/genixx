cmake_minimum_required(VERSION 3.14)

add_library(genixx-utils INTERFACE)

add_library(genixx::utils ALIAS genixx-utils)

target_include_directories(genixx-utils
    INTERFACE include)

target_link_libraries(genixx-utils
    INTERFACE genixx::error fmt)

target_compile_features(genixx-utils INTERFACE cxx_std_17)
