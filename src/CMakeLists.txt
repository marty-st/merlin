include_directories(
    # "${PROJECT_SOURCE_DIR}/src/app/include" // Uncomment when app/include has .hpp files
    "${PROJECT_SOURCE_DIR}/src/osi/include"
    )

set(MERLIN_LIBRARIES_TO_LINK_WITH
    # app // Uncomment when app/include has .hpp files
    osi
    )

message("Including the following libraries to the build:")
add_subdirectory(./osi)
message("-- osi")

message("Including the following executables to the build:")
add_subdirectory(./app)
message("-- app")