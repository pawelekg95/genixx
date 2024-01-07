include(FetchContent)
FetchContent_Declare(
    rethreadme
    GIT_REPOSITORY  https://github.com/pawelekg95/reThreadMe.git
    GIT_TAG         9405727b385b3be1d7db52906b119987343c5316
)

FetchContent_GetProperties(rethreadme)
if (NOT rethreadme_POPULATED)
    FetchContent_Populate(rethreadme)
    add_subdirectory(${rethreadme_SOURCE_DIR}/lib ${rethreadme_BINARY_DIR})
endif ()
