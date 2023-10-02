# genixx
## Create your own genetic algorithm with ease. 
Copyright (c) 2022 Pawel Gmurczyk

Documentation:
* [Reference](https://pawelekg95.github.io/genixx/)

# Introduction
Easy-to-use, flexible framework to create complex genetic algorithms.

# Installation

### CMake
To include genixx simply put:

```
include(FetchContent)
FetchContent_Declare(
    calgopp
    GIT_REPOSITORY  https://github.com/pawelekg95/genixx.git
    GIT_TAG         main
)

FetchContent_GetProperties(genixx)
FetchContent_Populate(genixx)

add_subdirectory(${genixx_SOURCE_DIR}/lib ${genixx_BINARY_DIR})
```

in your top level CMakeLists.txt and in CMakeLists.txt of every module that is supposed to link with
genixx:

````
target_link_libraries(<your_module>
    PUBLIC genixx::<submodule>
)
````

# Usage
See `example` directory for examples.
