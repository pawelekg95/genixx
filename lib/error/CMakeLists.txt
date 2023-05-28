cmake_minimum_required(VERSION 3.14)

add_library(genixx-error INTERFACE)

add_library(genixx::error ALIAS genixx-error)

target_include_directories(genixx-error
    INTERFACE include)
