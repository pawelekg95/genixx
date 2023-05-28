cmake_minimum_required(VERSION 3.14)

add_library(genixx-chromosome INTERFACE)

add_library(genixx::chromosome ALIAS genixx-chromosome)

target_include_directories(genixx-chromosome
INTERFACE include)
