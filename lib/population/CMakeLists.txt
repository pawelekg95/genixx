cmake_minimum_required(VERSION 3.14)

add_library(genixx-population EXCLUDE_FROM_ALL
    Individual.cpp
    Population.cpp)

add_library(genixx::population ALIAS genixx-population)

target_include_directories(genixx-population
    PUBLIC include)

target_link_libraries(genixx-population
    PUBLIC rethreadme genixx::error genixx::utils genixx::chromosome
    )
