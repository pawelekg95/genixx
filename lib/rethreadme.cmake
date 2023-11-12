include(FetchContent)
FetchContent_Declare(
    rethreadme
    GIT_REPOSITORY  https://github.com/pawelekg95/reThreadMe.git
    GIT_TAG         ed10fd10ebc51de8b42418137e94ce994bda2d57
)

FetchContent_GetProperties(rethreadme)
FetchContent_Populate(rethreadme)

add_subdirectory(${rethreadme_SOURCE_DIR}/lib ${rethreadme_BINARY_DIR})
