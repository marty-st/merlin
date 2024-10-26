include_directories(
    "${PROJECT_SOURCE_DIR}/src/app/include"
    "${PROJECT_SOURCE_DIR}/src/osi/include"
    "${PROJECT_SOURCE_DIR}/src/util/include"
    )

set(MERLIN_LIBRARIES_TO_LINK_WITH
    # app # is executable
    osi
    util
    )

message("Including the following libraries to the build:")
add_subdirectory(./osi)
message("-- osi")
add_subdirectory(./util)
message("-- util")

message("Including the following executables to the build:")
add_subdirectory(./app)
message("-- app")
