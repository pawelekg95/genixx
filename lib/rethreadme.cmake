include(FetchContent)
FetchContent_Declare(
    rethreadme
    GIT_REPOSITORY  https://github.com/pawelekg95/reThreadMe.git
    GIT_TAG         ad3faa69b5763c73d5825d53c53aea2d308c9aab
)

FetchContent_GetProperties(rethreadme)
if (NOT rethreadme_POPULATED)
    FetchContent_Populate(rethreadme)
    add_subdirectory(${rethreadme_SOURCE_DIR}/lib ${rethreadme_BINARY_DIR})
endif ()
