cmake_minimum_required(VERSION 3.14)

add_library(genixx-utils INTERFACE)

add_library(genixx::utils ALIAS genixx-utils)

target_include_directories(genixx-utils
    INTERFACE include)
